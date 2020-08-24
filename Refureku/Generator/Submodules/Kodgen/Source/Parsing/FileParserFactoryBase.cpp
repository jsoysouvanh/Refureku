#include "Kodgen/Parsing/FileParserFactoryBase.h"

using namespace kodgen;

void FileParserFactoryBase::refreshBuildCommandStrings() noexcept
{
	_namespacePropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.namespaceMacroName	+ "(...)=__attribute__((annotate(\"KGN:\"#__VA_ARGS__)))";
	_classPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.classMacroName		+ "(...)=__attribute__((annotate(\"KGC:\"#__VA_ARGS__)))";
	_structPropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.structMacroName	+ "(...)=__attribute__((annotate(\"KGS:\"#__VA_ARGS__)))";
	_variablePropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.variableMacroName	+ "(...)=__attribute__((annotate(\"KGV:\"#__VA_ARGS__)))";
	_fieldPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.fieldMacroName		+ "(...)=__attribute__((annotate(\"KGF:\"#__VA_ARGS__)))";
	_functionPropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.functionMacroName	+ "(...)=__attribute__((annotate(\"KGFu:\"#__VA_ARGS__)))";
	_methodPropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.methodMacroName	+ "(...)=__attribute__((annotate(\"KGM:\"#__VA_ARGS__)))";
	_enumPropertyMacro		= "-D" + parsingSettings.propertyParsingSettings.enumMacroName		+ "(...)=__attribute__((annotate(\"KGE:\"#__VA_ARGS__)))";
	_enumValuePropertyMacro	= "-D" + parsingSettings.propertyParsingSettings.enumValueMacroName	+ "(...)=__attribute__((annotate(\"KGEV:\"#__VA_ARGS__)))";

	_projectIncludeDirs.clear();
	_projectIncludeDirs.reserve(parsingSettings.projectIncludeDirectories.size());

	for (fs::path const& includeDir : parsingSettings.projectIncludeDirectories)
	{
		_projectIncludeDirs.emplace_back("-I" + includeDir.string());
	}
}

void FileParserFactoryBase::refreshCompilationArguments() noexcept
{
	_compilationArguments.clear();

	refreshBuildCommandStrings();

	/**
	*	3 to include -xc++, -std=c++1z & _kodgenParsingMacro
	*
	*	9 because we make an additional parameter per possible entity
	*	Namespace, Class, Struct, Variable, Field, Function, Method, Enum, EnumValue
	*/
	_compilationArguments.reserve(3u + 9u + _projectIncludeDirs.size());

	//Parsing C++
	_compilationArguments.emplace_back("-xc++");

	//Use C++17
	_compilationArguments.emplace_back("-std=c++1z"); 

	//Macro set when we are parsing with Kodgen
	_compilationArguments.emplace_back(_kodgenParsingMacro.data());

	_compilationArguments.emplace_back(_namespacePropertyMacro.data());
	_compilationArguments.emplace_back(_classPropertyMacro.data());
	_compilationArguments.emplace_back(_structPropertyMacro.data());
	_compilationArguments.emplace_back(_variablePropertyMacro.data());
	_compilationArguments.emplace_back(_fieldPropertyMacro.data());
	_compilationArguments.emplace_back(_methodPropertyMacro.data());
	_compilationArguments.emplace_back(_functionPropertyMacro.data());
	_compilationArguments.emplace_back(_enumPropertyMacro.data());
	_compilationArguments.emplace_back(_enumValuePropertyMacro.data());

	for (std::string const& includeDir : _projectIncludeDirs)
	{
		_compilationArguments.emplace_back(includeDir.data());
	}
}

void FileParserFactoryBase::logCompilationArguments() noexcept
{
	if (logger != nullptr)
	{
		for (char const* arg : _compilationArguments)
		{
			logger->log(std::string(arg) + " ", ILogger::ELogSeverity::Info);
		}
	}
}

void FileParserFactoryBase::setupFileParser(kodgen::FileParser& fileParser) const noexcept
{
	fileParser.logger = logger;

	fileParser.parsingSettings = &parsingSettings;
}

void FileParserFactoryBase::_init() noexcept
{
	refreshCompilationArguments();

#if KODGEN_DEV
	logCompilationArguments();
#endif
}

bool FileParserFactoryBase::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value settings = toml::parse(pathToSettingsFile.string());

		if (settings.contains("FileParsingSettings"))
		{
			//Get the FileParserSettings table
			toml::value const& parserSettings = toml::find(settings, "FileParsingSettings");

			//Update Parsing settings
			TomlUtility::updateSetting(parserSettings, "shouldParseAllEntities", parsingSettings.shouldParseAllEntities);
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

std::vector<char const*> const& FileParserFactoryBase::getCompilationArguments() const noexcept
{
	return _compilationArguments;
}