#include "Parsing/FileParser.h"

#include <iostream>
#include <cassert>

#include "Misc/Helpers.h"
#include "InfoStructures/ParsingInfo.h"

using namespace kodgen;

FileParser::FileParser() noexcept:
	_clangIndex{clang_createIndex(0, 0)}
{
	//Propagate the parsing info to child parsers
	_classParser.setParsingInfo(&_parsingInfo);
	_enumParser.setParsingInfo(&_parsingInfo);
}

FileParser::~FileParser() noexcept
{
	clang_disposeIndex(_clangIndex);
}

CXChildVisitResult FileParser::staticParseCursor(CXCursor c, CXCursor parent, CXClientData clientData) noexcept
{
	FileParser*	parser = reinterpret_cast<FileParser*>(clientData);

	//Parse the given file ONLY, ignore headers
	if (clang_Location_isFromMainFile(clang_getCursorLocation (c)) || clang_getCursorKind(c) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return parser->parseCursor(c);
	}
	
	return CXChildVisitResult::CXChildVisit_Continue;
}

CXChildVisitResult FileParser::parseCursor(CXCursor currentCursor) noexcept
{
	//Check for namespace, class or enum
	switch (currentCursor.kind)
	{
		case CXCursorKind::CXCursor_Namespace:
			return CXChildVisitResult::CXChildVisit_Recurse;

		case CXCursorKind::CXCursor_ClassDecl:
			return parseClass(currentCursor, false);

		case CXCursorKind::CXCursor_StructDecl:
			return parseClass(currentCursor, true);

		case CXCursorKind::CXCursor_EnumDecl:
			return parseEnum(currentCursor);
	}

	return CXChildVisitResult::CXChildVisit_Continue;
}

CXChildVisitResult FileParser::parseClass(CXCursor classCursor, bool isStruct) noexcept
{
	if (isStruct)
	{
		assert(classCursor.kind == CXCursorKind::CXCursor_StructDecl);

		_classParser.startStructParsing(classCursor);
	}
	else
	{
		assert(classCursor.kind == CXCursorKind::CXCursor_ClassDecl);

		_classParser.startClassParsing(classCursor);
	}

	clang_visitChildren(classCursor, [](CXCursor c, CXCursor parent, CXClientData clientData)
						{
							ClassParser* classParser = reinterpret_cast<ClassParser*>(clientData);

							return classParser->parse(c);

						}, &_classParser);

	return _classParser.endParsing();
}

CXChildVisitResult FileParser::parseEnum(CXCursor enumCursor) noexcept
{
	assert(enumCursor.kind == CXCursorKind::CXCursor_EnumDecl);

	_enumParser.startParsing(enumCursor);

	clang_visitChildren(enumCursor, [](CXCursor c, CXCursor parent, CXClientData clientData)
						{
							EnumParser* enumParser = reinterpret_cast<EnumParser*>(clientData);

							return enumParser->parse(c);

						}, &_enumParser);

	return _enumParser.endParsing();
}

std::vector<char const*> FileParser::makeParseArguments() const noexcept
{
	static std::string			parsingMacro("-D" + _parsingMacro);
	static std::string			classPropertyMacro;
	static std::string			structPropertyMacro;
	static std::string			fieldPropertyMacro;
	static std::string			methodPropertyMacro;
	static std::string			enumPropertyMacro;
	static std::string			enumValuePropertyMacro;

	std::vector<char const*>	result;

	/**
	*	2 to include -xc++ & _parsingMacro
	*
	*	6 because we make an additional parameter per possible entity
	*	Class, Struct, Field, Method, Enum, EnumValue
	*/
	result.reserve(2u + 6u);

	//Parsing C++
	result.emplace_back("-xc++");

	//Macro set when we are parsing with Kodgen
	result.emplace_back(parsingMacro.data());

	//Refresh static entity property macros according to parsing settings
	ParsingSettings const& parsingSettings = _parsingInfo.parsingSettings;

	classPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.classPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGC:\"#__VA_ARGS__)))";
	structPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.structPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGS:\"#__VA_ARGS__)))";
	fieldPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.fieldPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGF:\"#__VA_ARGS__)))";
	methodPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.methodPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGM:\"#__VA_ARGS__)))";
	enumPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.enumPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGE:\"#__VA_ARGS__)))";
	enumValuePropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.enumValuePropertyRules.macroName	+ "(...)=__attribute__((annotate(\"KGEV:\"#__VA_ARGS__)))";

	result.emplace_back(classPropertyMacro.data());
	result.emplace_back(structPropertyMacro.data());
	result.emplace_back(fieldPropertyMacro.data());
	result.emplace_back(methodPropertyMacro.data());
	result.emplace_back(enumPropertyMacro.data());
	result.emplace_back(enumValuePropertyMacro.data());

	return result;
}

bool FileParser::parse(fs::path const& parseFile, ParsingResult& out_result) noexcept
{
	bool isSuccess = false;

	reset();

	preParse(parseFile);

	if (fs::exists(parseFile) && !fs::is_directory(parseFile))
	{
		std::vector<char const*> const parseArguments = makeParseArguments();

		//Parse the given file
		CXTranslationUnit translationUnit = clang_parseTranslationUnit(_clangIndex, parseFile.string().c_str(), parseArguments.data(), static_cast<int32>(parseArguments.size()), nullptr, 0, CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_Incomplete);

		if (translationUnit != nullptr)
		{
			//Get the root cursor for this translation unit
			CXCursor cursor = clang_getTranslationUnitCursor(translationUnit);
			
			if (clang_visitChildren(cursor, &FileParser::staticParseCursor, this) || _parsingInfo.hasErrorOccured())
			{
				//ERROR
			}
			else
			{
				_parsingInfo.flushCurrentStructOrClass();
				_parsingInfo.flushCurrentEnum();

				isSuccess = true;
			}

			#ifndef NDEBUG
			
			CXDiagnosticSet diagnostics = clang_getDiagnosticSetFromTU(translationUnit);

			std::cout << "DIAGNOSTICS START..." << std::endl;
			for (unsigned i = 0u; i < clang_getNumDiagnosticsInSet(diagnostics); i++)
			{
				CXDiagnostic diagnostic(clang_getDiagnosticInSet(diagnostics, i));
				std::cout << Helpers::getString(clang_formatDiagnostic(diagnostic, clang_defaultDiagnosticDisplayOptions())) << std::endl;
				clang_disposeDiagnostic(diagnostic);
			}
			std::cout << "DIAGNOSTICS END..." << std::endl;

			clang_disposeDiagnosticSet(diagnostics);

			#endif

			clang_disposeTranslationUnit(translationUnit);
		}
		else
		{
			_parsingInfo.parsingResult.parsingErrors.emplace_back(ParsingError(EParsingError::TranslationUnitInitFailed));
		}
	}
	else
	{
		_parsingInfo.parsingResult.parsingErrors.emplace_back(ParsingError(EParsingError::InexistantFile));
	}

	out_result = std::move(_parsingInfo.parsingResult);

	postParse(parseFile, out_result);

	return isSuccess;
}

void FileParser::preParse(fs::path const&) noexcept
{
	/**
	*	Default implementation does nothing special
	*/
}

void FileParser::postParse(fs::path const&, ParsingResult const&) noexcept
{
	/**
	*	Default implementation does nothing special
	*/
}

void FileParser::reset() noexcept
{
	_classParser.reset();
	_enumParser.reset();

	_parsingInfo.reset();
}

std::string const& FileParser::getParsingMacro() noexcept
{
	return _parsingMacro;
}

ParsingSettings& FileParser::getParsingSettings() noexcept
{
	return _parsingInfo.parsingSettings;
}