#include "Parsing/FileParser.h"

#include <cassert>

#include "Misc/Helpers.h"
#include "Misc/DisableWarningMacros.h"
#include "Misc/TomlUtility.h"

using namespace kodgen;

FileParser::FileParser() noexcept:
	_clangIndex{clang_createIndex(0, 0)}
{
}

FileParser::~FileParser() noexcept
{
	clang_disposeIndex(_clangIndex);
}

bool FileParser::parse(fs::path const& toParseFile, FileParsingResult& out_result) noexcept
{
	bool isSuccess = false;

	preParse(toParseFile);

	if (fs::exists(toParseFile) && !fs::is_directory(toParseFile))
	{
		//Fill the parsed file info
		out_result.parsedFile = toParseFile;

		std::vector<char const*> const compilationArguments = makeCompilationArguments();

#if KODGEN_DEV
		logCompilationArguments();
#endif

		//Parse the given file
		CXTranslationUnit translationUnit = clang_parseTranslationUnit(_clangIndex, toParseFile.string().c_str(), compilationArguments.data(), static_cast<int32>(compilationArguments.size()), nullptr, 0, CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_Incomplete | CXTranslationUnit_KeepGoing);

		if (translationUnit != nullptr)
		{
			ParsingContext& context = pushContext(translationUnit, out_result);

			if (clang_visitChildren(context.rootCursor, &FileParser::parseNestedEntity, this) || !out_result.errors.empty())
			{
				//ERROR
			}
			else
			{
				//Refresh all outer entities contained in the final result
				refreshOuterEntity(out_result);

				isSuccess = true;
			}

#if KODGEN_DEV
			logDiagnostic(translationUnit);
#endif

			popContext();

			//There should not have any context left once parsing has finished
			assert(contextsStack.empty());

			clang_disposeTranslationUnit(translationUnit);
		}
		else
		{
			out_result.errors.emplace_back(ParsingError(EParsingError::TranslationUnitInitFailed));
		}
	}
	else
	{
		out_result.errors.emplace_back(ParsingError(EParsingError::InexistantFile));
	}

	postParse(toParseFile, out_result);

	return isSuccess;
}

CXChildVisitResult FileParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	FileParser*		parser		= reinterpret_cast<FileParser*>(clientData);

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM
	
	CXChildVisitResult	visitResult = CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP

	//Parse the given file ONLY, ignore headers
	if (clang_Location_isFromMainFile(clang_getCursorLocation(cursor)))
	{
		//std::cout << "FILE => " << Helpers::getString(clang_getCursorKindSpelling(cursor.kind)) << " " << Helpers::getString(clang_getCursorDisplayName(cursor)) << std::endl;

		switch (cursor.kind)
		{
			case CXCursorKind::CXCursor_Namespace:
				parser->addNamespaceResult(parser->parseNamespace(cursor, visitResult));
				break;

			case CXCursorKind::CXCursor_StructDecl:
				[[fallthrough]];
			case CXCursorKind::CXCursor_ClassDecl:
				parser->addClassResult(parser->parseClass(cursor, visitResult));
				break;

			case CXCursorKind::CXCursor_EnumDecl:
				parser->addEnumResult(parser->parseEnum(cursor, visitResult));
				break;

			//TODO: Handle global variables
			//TODO: Handle free functions

			default:
				break;
		}
	}

	return visitResult;
}

ParsingContext& FileParser::pushContext(CXTranslationUnit const& translationUnit, FileParsingResult& out_result) noexcept
{
	_propertyParser.setup(parsingSettings.propertyParsingSettings);

	ParsingContext newContext;

	newContext.parentContext	= nullptr;
	newContext.rootCursor		= clang_getTranslationUnitCursor(translationUnit);
	newContext.propertyParser	= &_propertyParser;
	newContext.parsingSettings	= &parsingSettings;
	newContext.parsingResult	= &out_result;

	contextsStack.push(std::move(newContext));

	return getContext();
}

void FileParser::addNamespaceResult(NamespaceParsingResult&& result) noexcept
{
	if (result.parsedNamespace.has_value())
	{
		getParsingResult()->namespaces.emplace_back(std::move(result.parsedNamespace).value());
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		getContext().parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void FileParser::addClassResult(ClassParsingResult&& result) noexcept
{
	if (result.parsedClass.has_value())
	{
		switch (result.parsedClass->entityType)
		{
			case EntityInfo::EType::Struct:
				getParsingResult()->structs.emplace_back(std::move(result.parsedClass).value());
				break;

			case EntityInfo::EType::Class:
				getParsingResult()->classes.emplace_back(std::move(result.parsedClass).value());
				break;

			default:
				assert(false);	//Should never reach this line
				break;
		}
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		getContext().parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void FileParser::addEnumResult(EnumParsingResult&& result) noexcept
{
	if (result.parsedEnum.has_value())
	{
		getParsingResult()->enums.emplace_back(std::move(result.parsedEnum).value());
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		getContext().parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void FileParser::refreshOuterEntity(FileParsingResult& out_result) const noexcept
{
	for (NamespaceInfo& namespaceInfo : out_result.namespaces)
	{
		namespaceInfo.refreshOuterEntity();
	}

	for (StructClassInfo& structInfo : out_result.structs)
	{
		structInfo.refreshOuterEntity();
	}

	for (StructClassInfo& classInfo : out_result.classes)
	{
		classInfo.refreshOuterEntity();
	}

	for (EnumInfo& enumInfo : out_result.enums)
	{
		enumInfo.refreshOuterEntity();
	}
}

void FileParser::preParse(fs::path const&) noexcept
{
	/**
	*	Default implementation does nothing special
	*/
}

void FileParser::postParse(fs::path const&, FileParsingResult const&) noexcept
{
	/**
	*	Default implementation does nothing special
	*/
}

void FileParser::refreshBuildCommandStrings() noexcept
{
	_namespacePropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.namespacePropertyRules.macroName	+ "(...)=__attribute__((annotate(\"KGN:\"#__VA_ARGS__)))";
	_classPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.classPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGC:\"#__VA_ARGS__)))";
	_structPropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.structPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGS:\"#__VA_ARGS__)))";
	_fieldPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.fieldPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGF:\"#__VA_ARGS__)))";
	_methodPropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.methodPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGM:\"#__VA_ARGS__)))";
	_enumPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.enumPropertyRules.macroName		+ "(...)=__attribute__((annotate(\"KGE:\"#__VA_ARGS__)))";
	_enumValuePropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.enumValuePropertyRules.macroName	+ "(...)=__attribute__((annotate(\"KGEV:\"#__VA_ARGS__)))";

	_projectIncludeDirs.clear();
	_projectIncludeDirs.reserve(parsingSettings.projectIncludeDirectories.size());

	for (fs::path const& includeDir : parsingSettings.projectIncludeDirectories)
	{
		_projectIncludeDirs.emplace_back("-I" + includeDir.string());
	}
}

std::vector<char const*> FileParser::makeCompilationArguments() noexcept
{
	std::vector<char const*>	result;

	refreshBuildCommandStrings();

	/**
	*	3 to include -xc++, -std=c++1z & _kodgenParsingMacro
	*
	*	7 because we make an additional parameter per possible entity
	*	Namespace, Class, Struct, Field, Method, Enum, EnumValue
	*/
	result.reserve(3u + 7u + _projectIncludeDirs.size());

	//Parsing C++
	result.emplace_back("-xc++");

	//Use C++17
	result.emplace_back("-std=c++1z"); 

	//Macro set when we are parsing with Kodgen
	result.emplace_back(_kodgenParsingMacro.data());

	result.emplace_back(_namespacePropertyMacro.data());
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

void FileParser::logDiagnostic(CXTranslationUnit const& translationUnit) const noexcept
{
	if (logger != nullptr)
	{
		CXDiagnosticSet diagnostics = clang_getDiagnosticSetFromTU(translationUnit);

		logger->log("DIAGNOSTICS START...", ILogger::ELogSeverity::Info);

		for (unsigned i = 0u; i < clang_getNumDiagnosticsInSet(diagnostics); i++)
		{
			CXDiagnostic diagnostic(clang_getDiagnosticInSet(diagnostics, i));

			logger->log(Helpers::getString(clang_formatDiagnostic(diagnostic, clang_defaultDiagnosticDisplayOptions())), ILogger::ELogSeverity::Warning);

			clang_disposeDiagnostic(diagnostic);
		}

		logger->log("DIAGNOSTICS END...", ILogger::ELogSeverity::Info);

		clang_disposeDiagnosticSet(diagnostics);
	}
}

void FileParser::logCompilationArguments() noexcept
{
	if (logger != nullptr)
	{
		std::vector<char const*> const compilationArguments = makeCompilationArguments();

		for (char const* arg : compilationArguments)
		{
			logger->log(std::string(arg) + " ", ILogger::ELogSeverity::Info);
		}
	}
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
			TomlUtility::updateSetting(parserSettings, "shouldAbortParsingOnFirstError", parsingSettings.shouldAbortParsingOnFirstError);
			TomlUtility::updateSetting(parserSettings, "projectIncludeDirectories", parsingSettings.projectIncludeDirectories);

			//Update Property settings
			if (parserSettings.contains("Properties"))
			{
				parsingSettings.propertyParsingSettings.loadSettings(toml::find(parserSettings, "Properties"));
			}
		}

		return true;
	}
	catch (std::runtime_error const& /* exception */)
	{
	}
	catch (toml::syntax_error const& exception)
	{
		if (logger != nullptr)
		{
			logger->log("Syntax error in settings file.\n" + std::string(exception.what()), ILogger::ELogSeverity::Error);
		}
	}

	return false;
}