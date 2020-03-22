#include "Parsing/FileParser.h"

#include <iostream>

#include "Misc/Helpers.h"
#include "InfoStructures/ParsingInfo.h"

using namespace kodgen;

FileParser::FileParser() noexcept:
	_clangIndex{clang_createIndex(0, 0)}
{
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
		parser->updateParsingState(parent);

		return parser->parseCursor(c);
	}
	
	return CXChildVisitResult::CXChildVisit_Continue;
}

void FileParser::updateParsingState(CXCursor parent) noexcept
{
	if (_classParser.getParsingLevel())
	{
		_classParser.updateParsingState(parent, _parsingInfo);
	}
	else if (_enumParser.getParsingLevel())
	{
		_enumParser.updateParsingState(parent, _parsingInfo);
	}
}

CXChildVisitResult FileParser::parseCursor(CXCursor currentCursor) noexcept
{
	if (_classParser.getParsingLevel())			//Currently parsing a class of struct
	{
		return _classParser.parse(currentCursor, _parsingInfo);
	}
	else if (_enumParser.getParsingLevel())		//Currently parsing an enum
	{	
		return _enumParser.parse(currentCursor, _parsingInfo);
	}
	else										//Looking for something to parse
	{
		return parseDefault(currentCursor);
	}
}

CXChildVisitResult FileParser::parseDefault(CXCursor currentCursor) noexcept
{
	CXCursorKind cursorKind	= clang_getCursorKind(currentCursor);

	//Check for namespace, class or enum
	switch (cursorKind)
	{
		case CXCursorKind::CXCursor_Namespace:
			//TODO
			break;

		case CXCursorKind::CXCursor_ClassDecl:
			_classParser.startClassParsing(currentCursor, _parsingInfo);
			break;

		case CXCursorKind::CXCursor_StructDecl:
			_classParser.startStructParsing(currentCursor, _parsingInfo);
			break;

		case CXCursorKind::CXCursor_EnumDecl:
			_enumParser.startParsing(currentCursor);
			break;

		default:
			return CXChildVisitResult::CXChildVisit_Continue; 
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
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