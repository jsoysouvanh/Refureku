#include "Kodgen/Parsing/FileParserFactoryBase.h"

#include "Kodgen/Misc/Helpers.h"
#include "Kodgen/Misc/CompilerHelpers.h"

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

	//Setup project include directories
	std::vector<fs::path> nativeIncludeDirectories;
	
	try
	{
		if (!parsingSettings.getCompilerExeName().empty())
		{
			nativeIncludeDirectories = CompilerHelpers::getCompilerNativeIncludeDirectories(parsingSettings.getCompilerExeName());

			if (nativeIncludeDirectories.empty())
			{
				logger->log("Could not find any include directory from the specified compiler. Make sure the compiler is installed on your computer.", kodgen::ILogger::ELogSeverity::Warning);
			}
		}
		else
		{
			logger->log("FileParserFactory compiler must be set to parse files.", kodgen::ILogger::ELogSeverity::Error);
		}
	}
	catch (std::exception const& e)
	{
		logger->log(e.what(), kodgen::ILogger::ELogSeverity::Error);
	}

	_projectIncludeDirs.clear();
	_projectIncludeDirs.reserve(parsingSettings.getProjectIncludeDirectories().size() + nativeIncludeDirectories.size());

	//Add user manually specified include directories
	for (fs::path const& includeDir : parsingSettings.getProjectIncludeDirectories())
	{
		_projectIncludeDirs.emplace_back("-I" + includeDir.string());
	}

	//Add compiler native include directories
	for (fs::path& includeDir : nativeIncludeDirectories)
	{
		_projectIncludeDirs.emplace_back("-I" + includeDir.string());
	}
}

void FileParserFactoryBase::refreshCompilationArguments() noexcept
{
	_compilationArguments.clear();

	refreshBuildCommandStrings();

#if KODGEN_DEV
	constexpr size_t baseCompilationArgCount = 4u;	//-xc++, -v, -std=c++1z & _kodgenParsingMacro
#else
	constexpr size_t baseCompilationArgCount = 3u;	//-xc++, -std=c++1z & _kodgenParsingMacro
#endif

	/**
	*	3 to include -xc++, -std=c++1z & _kodgenParsingMacro
	*
	*	9 because we make an additional parameter per possible entity
	*	Namespace, Class, Struct, Variable, Field, Function, Method, Enum, EnumValue
	*/
	_compilationArguments.reserve(baseCompilationArgCount + 9u + _projectIncludeDirs.size());

	//Parsing C++
	_compilationArguments.emplace_back("-xc++");

#if KODGEN_DEV
	_compilationArguments.emplace_back("-v");
#endif

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

void FileParserFactoryBase::loadShouldParseAllEntities(toml::value const& tomlFileParsingSettings) noexcept
{
	if (TomlUtility::updateSetting(tomlFileParsingSettings, "shouldParseAllEntities", parsingSettings.shouldParseAllEntities, logger) && logger != nullptr)
	{
		logger->log("[TOML] Load shouldParseAllEntities: " + Helpers::toString(parsingSettings.shouldParseAllEntities));
	}
}

void FileParserFactoryBase::loadShouldAbortParsingOnFirstError(toml::value const& tomlFileParsingSettings) noexcept
{
	if (TomlUtility::updateSetting(tomlFileParsingSettings, "shouldAbortParsingOnFirstError", parsingSettings.shouldAbortParsingOnFirstError, logger) && logger != nullptr)
	{
		logger->log("[TOML] Load shouldAbortParsingOnFirstError: " + Helpers::toString(parsingSettings.shouldAbortParsingOnFirstError));
	}
}

void FileParserFactoryBase::loadShouldLogDiagnostic(toml::value const& tomlFileParsingSettings) noexcept
{
	if (TomlUtility::updateSetting(tomlFileParsingSettings, "shouldLogDiagnostic", parsingSettings.shouldLogDiagnostic, logger) && logger != nullptr)
	{
		logger->log("[TOML] Load shouldLogDiagnostic: " + Helpers::toString(parsingSettings.shouldLogDiagnostic));
	}
}

void FileParserFactoryBase::loadProjectIncludeDirectories(toml::value const& tomlFileParsingSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> includeDirectories;
	
	if (TomlUtility::updateSetting(tomlFileParsingSettings, "projectIncludeDirectories", includeDirectories, logger))
	{
		for (fs::path const& includeDirectoryPath : includeDirectories)
		{
			bool success = parsingSettings.addProjectIncludeDirectory(includeDirectoryPath);

			//Log load result
			if (logger != nullptr)
			{
				if (success)
				{
					logger->log("[TOML] Load new project include directory: " + FilesystemHelpers::sanitizePath(includeDirectoryPath).string());
				}
				else
				{
					logger->log("[TOML] Discard project include directory as it doesn't exist or is not a directory: " + includeDirectoryPath.string(), ILogger::ELogSeverity::Warning);
				}
			}
		}
	}
}

void FileParserFactoryBase::loadCompilerExeName(toml::value const& tomlFileParsingSettings) noexcept
{
	std::string compilerExeName;
	
	if (TomlUtility::updateSetting(tomlFileParsingSettings, "compilerExeName", compilerExeName, logger))
	{
		bool success = parsingSettings.setCompilerExeName(compilerExeName);

		if (logger != nullptr)
		{
			if (success)
			{
				logger->log("[TOML] Load compiler: " + compilerExeName);
			}
			else
			{
				logger->log("[TOML] " + compilerExeName + " doesn't exist, is not supported or could not be run on the current computer.", ILogger::ELogSeverity::Error);
			}
		}
	}
}

bool FileParserFactoryBase::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value tomlContent = toml::parse(pathToSettingsFile.string());

		if (tomlContent.contains(_tomlSettingsSectionName))
		{
			//Get the FileParserSettings table
			toml::value const& tomlFileParsingSettings = toml::find(tomlContent, _tomlSettingsSectionName);

			//Load settings from the table
			loadShouldParseAllEntities(tomlFileParsingSettings);
			loadShouldAbortParsingOnFirstError(tomlFileParsingSettings);
			loadShouldLogDiagnostic(tomlFileParsingSettings);
			loadProjectIncludeDirectories(tomlFileParsingSettings);
			loadCompilerExeName(tomlFileParsingSettings);

			//Update Property settings
			if (tomlFileParsingSettings.contains("Properties"))
			{
				parsingSettings.propertyParsingSettings.loadSettings(toml::find(tomlFileParsingSettings, "Properties"), logger);
			}
		}
		else if (logger != nullptr)
		{
			logger->log("Could not find the [" + std::string(_tomlSettingsSectionName) + "] section in the TOML file.", ILogger::ELogSeverity::Warning);
		}

		return true;
	}
	catch (std::runtime_error const& /* exception */)
	{
		//Failed to open the file
		if (logger != nullptr)
		{
			logger->log("Failed to load file parsing settings at " + pathToSettingsFile.string(), ILogger::ELogSeverity::Error);
		}
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