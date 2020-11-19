#include "Kodgen/CodeGen/FileGenerator.h"

#include <fstream>	//fstream

using namespace kodgen;

std::set<fs::path> FileGenerator::identifyFilesToProcess(FileGenerationResult& out_genResult, bool forceRegenerateAll) const noexcept
{
	std::set<fs::path> result;

	//Iterate over all "toParseFiles"
	for (fs::path path : settings.getToParseFiles())
	{
		if (fs::exists(path) && !fs::is_directory(path))
		{
			if (forceRegenerateAll || shouldRegenerateFile(path))
			{
				result.emplace(path);
			}
			else
			{
				out_genResult.upToDateFiles.push_back(path);
			}
		}
		else
		{
			//Add FileGenerationFile invalid path
			out_genResult.fileGenerationErrors.emplace_back(path, "", "This path was find in the toParseFiles list but it doesn't exist or is not a file.");
			logger->log("File " + path.string() + " doesn't exist", ILogger::ELogSeverity::Warning);
		}
	}

	//Iterate over all "toParseDirectories"
	for (fs::path pathToIncludedDir : settings.getToParseDirectories())
	{
		if (fs::exists(pathToIncludedDir) && fs::is_directory(pathToIncludedDir))
		{
			for (fs::recursive_directory_iterator directoryIt = fs::recursive_directory_iterator(pathToIncludedDir, fs::directory_options::follow_directory_symlink); directoryIt != fs::recursive_directory_iterator(); directoryIt++)
			{
				fs::directory_entry entry = *directoryIt;

				//Just to make sure the entry hasn't been deleted since beginning of directory iteration
				if (entry.exists())
				{
					if (entry.is_regular_file())
					{
						if (settings.supportedExtensions.find(entry.path().extension().string()) != settings.supportedExtensions.cend() &&	//supported extension
							settings.getIgnoredFiles().find(entry.path()) == settings.getIgnoredFiles().cend())								//file is not ignored
						{
							if (forceRegenerateAll || shouldRegenerateFile(entry.path()))
							{
								result.emplace(entry.path());
							}
							else
							{
								out_genResult.upToDateFiles.push_back(entry.path());
							}
						}
					}
					else if (entry.is_directory() && settings.getIgnoredDirectories().find(entry.path()) != settings.getIgnoredDirectories().cend())	//directory is ignored
					{
						//Don't iterate on ignored directory content
						directoryIt.disable_recursion_pending();
					}
				}
			}
		}
		else
		{
			//Add FileGenerationFile invalid path
			//out_genResult.fileGenerationErrors.emplace_back(pathToIncludedDir, "", "This path was find in the toParseDirectories list but it doesn't exist or is not a directory.");
			logger->log("Directory " + pathToIncludedDir.string() + " doesn't exist", ILogger::ELogSeverity::Warning);
		}
	}

	return result;
}

bool FileGenerator::shouldRegenerateFile(fs::path const& filePath) const noexcept
{
	fs::path pathToGeneratedFile = makePathToGeneratedFile(filePath);

	return !fs::exists(pathToGeneratedFile) || fs::last_write_time(filePath) > fs::last_write_time(pathToGeneratedFile);
}

fs::path FileGenerator::makePathToGeneratedFile(fs::path const& sourceFilePath) const noexcept
{
	assert(fs::exists(sourceFilePath) && fs::is_regular_file(sourceFilePath));

	return (settings.getOutputDirectory() / sourceFilePath.filename()).replace_extension(settings.generatedFilesExtension);
}

void FileGenerator::addGeneratedCodeTemplate(std::string const& templateName, GeneratedCodeTemplate* codeTemplate) noexcept
{
	if (codeTemplate != nullptr)
	{
		settings._generatedCodeTemplates[templateName] = codeTemplate;

		_generatedCodeTemplatePropertyRule.validTemplateNames.insert(templateName);
	}
}

bool FileGenerator::setDefaultGeneratedCodeTemplate(EEntityType entityType, std::string const& templateName) noexcept
{
	decltype(settings._generatedCodeTemplates)::const_iterator it = settings._generatedCodeTemplates.find(templateName);

	if (it != settings._generatedCodeTemplates.cend())
	{
		settings._defaultGeneratedCodeTemplates[entityType] = it->second;

		return true;
	}

	return false;
}

void FileGenerator::addNativePropertyRules(PropertyParsingSettings& propParsingSettings) const noexcept
{
	propParsingSettings.simplePropertyRules.push_back(&_parseAllNestedPropertyRule);
	propParsingSettings.complexPropertyRules.push_back(&_generatedCodeTemplatePropertyRule);
}

void FileGenerator::clearNativePropertyRules(PropertyParsingSettings& propParsingSettings) const noexcept
{
	propParsingSettings.simplePropertyRules.pop_back();		//Remove _parseAllNestedPropertyRule
	propParsingSettings.complexPropertyRules.pop_back();	//Remove _generatedCodeTemplatePropertyRule
}

void FileGenerator::generateMacrosFile(FileParserFactoryBase& fileParserFactory) const noexcept
{
	GeneratedFile macrosDefinitionFile(settings.getOutputDirectory() / settings.entityMacrosFilename);

	PropertyParsingSettings& pps = fileParserFactory.parsingSettings.propertyParsingSettings;

	//Define empty entity macros to allow compilation outside of the Kodgen parsing
	macrosDefinitionFile.writeLines("#pragma once",
									"",
									"#ifndef " + FileParserFactoryBase::parsingMacro,
									"",
									"#define " + pps.namespaceMacroName	+ "(...)",
									"#define " + pps.classMacroName		+ "(...)",
									"#define " + pps.structMacroName	+ "(...)",
									"#define " + pps.variableMacroName	+ "(...)",
									"#define " + pps.fieldMacroName		+ "(...)",
									"#define " + pps.methodMacroName	+ "(...)",
									"#define " + pps.enumMacroName		+ "(...)",
									"#define " + pps.enumValueMacroName	+ "(...)",
									"#define " + pps.functionMacroName	+ "(...)");

	macrosDefinitionFile.writeLine("\n#endif");
}

void FileGenerator::generateMissingMetadataFiles(std::set<fs::path> const& files) const noexcept
{
	for (fs::path const& file : files)
	{
		assert(fs::exists(file) && fs::is_regular_file(file));

		fs::path generatedFile = makePathToGeneratedFile(file);

		//Generate metadata file if it doesn't exist yet
		if (!fs::exists(generatedFile))
		{
			std::fstream file(generatedFile, std::ios::out);
		}
	}
}

void FileGenerator::setupFileGenerationUnit(FileGenerationUnit& fileGenerationUnit) const noexcept
{
	fileGenerationUnit.logger		= logger;
	fileGenerationUnit._settings	= &settings;
}

void FileGenerator::checkGenerationSettings() const noexcept
{
	auto& ignoredDirectories = settings.getIgnoredDirectories();

	//Emit a warning if the output directory content is going to be parsed
	if (fs::exists(settings.getOutputDirectory()) &&											//abort check if the output directory doesn't exist
		!fs::is_empty(settings.getOutputDirectory()) &&											//abort check if the output directory is empty
		ignoredDirectories.find(settings.getOutputDirectory()) == ignoredDirectories.cend())	//abort check if the output directory is already ignored
	{
		for (fs::path const& parsedDirectory : settings.getToParseDirectories())
		{
			if (FilesystemHelpers::isChildPath(settings.getOutputDirectory(), parsedDirectory))
			{
				if (logger != nullptr)
				{
					logger->log("Output directory is contained in a parsed directory, hence generated files will be parsed. If this is not intended, add the output directory to the list of ignored directories.", ILogger::ELogSeverity::Warning);
				}

				break;
			}
		}
	}
}

void FileGenerator::loadGeneratedFilesExtension(toml::value const& tomlGeneratorSettings) noexcept
{
	if (TomlUtility::updateSetting(tomlGeneratorSettings, "generatedFilesExtension", settings.generatedFilesExtension, logger) && logger != nullptr)
	{
		logger->log("[TOML] Load generatedFilesExtension: " + settings.generatedFilesExtension);
	}
}

void FileGenerator::loadEntityMacrosFilename(toml::value const& tomlGeneratorSettings) noexcept
{
	if (TomlUtility::updateSetting(tomlGeneratorSettings, "entityMacrosFilename", settings.entityMacrosFilename, logger) && logger != nullptr)
	{
		logger->log("[TOML] Load entityMacrosFilename: " + settings.entityMacrosFilename);
	}
}

void FileGenerator::loadSupportedExtensions(toml::value const& tomlGeneratorSettings) noexcept
{
	//Clear supported extensions before loading
	settings.supportedExtensions.clear();

	std::unordered_set<std::string> loadedExtensions;
	if (TomlUtility::updateSetting(tomlGeneratorSettings, "supportedExtensions", loadedExtensions, logger) && logger != nullptr)
	{
		for (std::string const& extension : loadedExtensions)
		{
			//TODO: might add extension validity check later
			settings.supportedExtensions.emplace(extension);

			if (logger != nullptr)
			{
				logger->log("[TOML] Load new supported extension: " + extension);
			}
		}
	}
}

void FileGenerator::loadOutputDirectory(toml::value const& tomlGeneratorSettings) noexcept
{
	std::string loadedOutputDirectory;

	if (TomlUtility::updateSetting(tomlGeneratorSettings, "outputDirectory", loadedOutputDirectory, logger))
	{
		bool success = settings.setOutputDirectory(loadedOutputDirectory);
		
		if (logger != nullptr)
		{
			if (success)
			{
				logger->log("[TOML] Load output directory: " + settings.getOutputDirectory().string());
			}
			else
			{
				logger->log("[TOML] Failed to load outputDirectory, file or invalid path: " + loadedOutputDirectory);
			}
		}
	}
}

void FileGenerator::loadToParseFiles(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> toParseFiles;

	settings.clearToParseFiles();

	if (TomlUtility::updateSetting(tomlGeneratorSettings, "toParseFiles", toParseFiles, logger))
	{
		bool success;

		for (fs::path const& path : toParseFiles)
		{
			success = settings.addToParseFile(path);

			if (logger != nullptr)
			{
				if (success)
				{
					logger->log("[TOML] Load new file to parse: " + FilesystemHelpers::sanitizePath(path).string());
				}
				else
				{
					logger->log("[TOML] Failed to add toParseFile as it doesn't exist, is not a file or is already part of the list of files to parse: " + path.string(), ILogger::ELogSeverity::Warning);
				}
			}
		}
	}
}

void FileGenerator::loadToParseDirectories(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> toParseDirectories;

	settings.clearToParseDirectories();

	if (TomlUtility::updateSetting(tomlGeneratorSettings, "toParseDirectories", toParseDirectories, logger))
	{
		bool success;

		for (fs::path const& path : toParseDirectories)
		{
			success = settings.addToParseDirectory(path);

			if (logger != nullptr)
			{
				if (success)
				{
					logger->log("[TOML] Load new directory to parse: " + FilesystemHelpers::sanitizePath(path).string());
				}
				else
				{
					logger->log("[TOML] Failed to add toParseDirectory as it doesn't exist, is not a directory or is already part of the list of directories to parse: " + path.string(), ILogger::ELogSeverity::Warning);
				}
			}
		}
	}
}

void FileGenerator::loadIgnoredFiles(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> ignoredFiles;

	settings.clearIgnoredFiles();

	if (TomlUtility::updateSetting(tomlGeneratorSettings, "ignoredFiles", ignoredFiles, logger))
	{
		bool success;

		for (fs::path const& path : ignoredFiles)
		{
			success = settings.addIgnoredFile(path);

			if (logger != nullptr)
			{
				if (success)
				{
					logger->log("[TOML] Load new ignored file: " + FilesystemHelpers::sanitizePath(path).string());
				}
				else
				{
					logger->log("[TOML] Failed to add ignoredFile as it doesn't exist, is not a file or is already part of the list of ignored files: " + path.string(), ILogger::ELogSeverity::Warning);
				}
			}
		}
	}
}

void FileGenerator::loadIgnoredDirectories(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> ignoredDirectories;

	settings.clearIgnoredDirectories();

	if (TomlUtility::updateSetting(tomlGeneratorSettings, "ignoredDirectories", ignoredDirectories, logger))
	{
		bool success;

		for (fs::path const& path : ignoredDirectories)
		{
			success = settings.addIgnoredDirectory(path);

			if (logger != nullptr)
			{
				if (success)
				{
					logger->log("[TOML] Load new ignored directory: " + FilesystemHelpers::sanitizePath(path).string());
				}
				else
				{
					logger->log("[TOML] Failed to add ignoredDirectory as it doesn't exist, is not a directory or is already part of the list of ignored directories: " + path.string(), ILogger::ELogSeverity::Warning);
				}
			}
		}
	}
}

bool FileGenerator::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value tomlContent = toml::parse(pathToSettingsFile.string());

		if (tomlContent.contains(_tomlSettingsSectionName))
		{
			toml::value const& tomlGeneratorSettings = toml::find(tomlContent, _tomlSettingsSectionName);

			loadGeneratedFilesExtension(tomlGeneratorSettings);
			loadEntityMacrosFilename(tomlGeneratorSettings);
			loadSupportedExtensions(tomlGeneratorSettings);
			loadOutputDirectory(tomlGeneratorSettings);
			loadToParseFiles(tomlGeneratorSettings);
			loadToParseDirectories(tomlGeneratorSettings);
			loadIgnoredFiles(tomlGeneratorSettings);
			loadIgnoredDirectories(tomlGeneratorSettings);
		}
		else if (logger != nullptr)
		{
			logger->log("Could not find the [" + std::string(_tomlSettingsSectionName) + "] section in the TOML file.", ILogger::ELogSeverity::Warning);
		}

		return true;
	}
	catch (std::runtime_error const&)
	{
		//Failed to open the file
		if (logger != nullptr)
		{
			logger->log("Failed to load file generation settings at " + pathToSettingsFile.string(), ILogger::ELogSeverity::Error);
		}
	}
	catch (toml::syntax_error const& e)
	{
		if (logger != nullptr)
		{
			logger->log("Syntax error in settings file.\n" + std::string(e.what()), ILogger::ELogSeverity::Error);
		}
	}

	return false;
}