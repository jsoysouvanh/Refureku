#include "Parsing/FileParser.h"

#include <iostream>
#include <cassert>

#include "Misc/Helpers.h"
#include "Misc/DisableWarningMacros.h"
#include "Misc/TomlUtility.h"
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

DISABLE_WARNING_PUSH
DISABLE_WARNING_UNSCOPED_ENUM

CXChildVisitResult FileParser::staticParseCursor(CXCursor c, CXCursor /* parent */, CXClientData clientData) noexcept
{
	FileParser*	parser = reinterpret_cast<FileParser*>(clientData);

	//Parse the given file ONLY, ignore headers
	if (clang_Location_isFromMainFile(clang_getCursorLocation (c)))
	{
		return parser->parseCursor(c);
	}
	
	return CXChildVisitResult::CXChildVisit_Continue;
}

DISABLE_WARNING_POP

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

		default:
			break;
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

	clang_visitChildren(classCursor, [](CXCursor c, CXCursor, CXClientData clientData)
						{
							return reinterpret_cast<ClassParser*>(clientData)->parse(c);

						}, &_classParser);

	return _classParser.endParsing();
}

CXChildVisitResult FileParser::parseEnum(CXCursor enumCursor) noexcept
{
	assert(enumCursor.kind == CXCursorKind::CXCursor_EnumDecl);

	_enumParser.startParsing(enumCursor);

	clang_visitChildren(enumCursor, [](CXCursor c, CXCursor, CXClientData clientData)
						{
							return reinterpret_cast<EnumParser*>(clientData)->parse(c);

						}, &_enumParser);

	return _enumParser.endParsing();
}

void FileParser::refreshBuildCommandStrings() noexcept
{
	ParsingSettings const& ps = _parsingInfo.parsingSettings;

	_classPropertyMacro		= "-D" + ps.propertyParsingSettings.classPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGC:\"#__VA_ARGS__)))";
	_structPropertyMacro	= "-D" + ps.propertyParsingSettings.structPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGS:\"#__VA_ARGS__)))";
	_fieldPropertyMacro		= "-D" + ps.propertyParsingSettings.fieldPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGF:\"#__VA_ARGS__)))";
	_methodPropertyMacro	= "-D" + ps.propertyParsingSettings.methodPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGM:\"#__VA_ARGS__)))";
	_enumPropertyMacro		= "-D" + ps.propertyParsingSettings.enumPropertyRules.macroName			+ "(...)=__attribute__((annotate(\"KGE:\"#__VA_ARGS__)))";
	_enumValuePropertyMacro	= "-D" + ps.propertyParsingSettings.enumValuePropertyRules.macroName	+ "(...)=__attribute__((annotate(\"KGEV:\"#__VA_ARGS__)))";

	_projectIncludeDirs.clear();
	_projectIncludeDirs.reserve(ps.projectIncludeDirectories.size());

	for (fs::path const& includeDir : ps.projectIncludeDirectories)
	{
		_projectIncludeDirs.emplace_back("-I" + includeDir.string());
	}
}

std::vector<char const*> FileParser::makeParseArguments() noexcept
{
	std::vector<char const*>	result;

	refreshBuildCommandStrings();

	/**
	*	3 to include -xc++, -sed=c++1z & _parsingMacro
	*
	*	6 because we make an additional parameter per possible entity
	*	Class, Struct, Field, Method, Enum, EnumValue
	*/
	result.reserve(3u + 6u + _projectIncludeDirs.size());

	//Parsing C++
	result.emplace_back("-xc++");

	//Use C++17
	result.emplace_back("-std=c++1z"); 

	//Macro set when we are parsing with Kodgen
	result.emplace_back(_kodgenParsingMacro.data());

	result.emplace_back(_classPropertyMacro.data());
	result.emplace_back(_structPropertyMacro.data());
	result.emplace_back(_fieldPropertyMacro.data());
	result.emplace_back(_methodPropertyMacro.data());
	result.emplace_back(_enumPropertyMacro.data());
	result.emplace_back(_enumValuePropertyMacro.data());
	
	for (std::string const& includeDir : _projectIncludeDirs)
	{
		result.emplace_back(includeDir.data());
	}

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

		#if KODGEN_DEV

		for (char const* arg : parseArguments)
		{
			std::cout << arg << " ";
		}

		std::cout << std::endl;

		#endif

		//Parse the given file
		CXTranslationUnit translationUnit = clang_parseTranslationUnit(_clangIndex, parseFile.string().c_str(), parseArguments.data(), static_cast<int32>(parseArguments.size()), nullptr, 0, CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_Incomplete | CXTranslationUnit_KeepGoing);

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
				isSuccess = true;
			}

			#if KODGEN_DEV
			
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

bool FileParser::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value settings = toml::parse(pathToSettingsFile.string());

		if (settings.contains("FileParserSettings"))
		{
			//Get the FileParserSettings table
			toml::value const& parserSettings = toml::find(settings, "FileParserSettings");

			//Update Parsing settings
			TomlUtility::updateSetting(parserSettings, "shouldAbortParsingOnFirstError", _parsingInfo.parsingSettings.shouldAbortParsingOnFirstError);
			TomlUtility::updateSetting(parserSettings, "projectIncludeDirectories", _parsingInfo.parsingSettings.projectIncludeDirectories);

			//Update Property settings
			if (parserSettings.contains("Properties"))
			{
				_parsingInfo.parsingSettings.propertyParsingSettings.loadSettings(toml::find(parserSettings, "Properties"));
			}
		}

		return true;
	}
	catch (std::runtime_error const&)
	{
	}
	catch (toml::syntax_error const& e)
	{
		std::cerr << "Syntax error in settings file." << std::endl << e.what() << std::endl;
	}

	return false;
}