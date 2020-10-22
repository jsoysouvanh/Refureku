#include "Kodgen/CodeGen/FileGenerator.h"

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
				result.emplace(fs::canonical(path.make_preferred()));
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
					fs::path entryPath = entry.path();

					if (entry.is_regular_file())
					{
						if (settings.supportedExtensions.find(entryPath.extension().string()) != settings.supportedExtensions.cend() &&	//supported extension
							settings.getIgnoredFiles().find(entryPath.string()) == settings.getIgnoredFiles().cend())					//file is not ignored
						{
							if (forceRegenerateAll || shouldRegenerateFile(entryPath))
							{
								result.emplace(fs::canonical(entryPath));
							}
							else
							{
								out_genResult.upToDateFiles.push_back(entryPath);
							}
						}
					}
					else if (entry.is_directory() && settings.getIgnoredDirectories().find(entryPath.string()) != settings.getIgnoredDirectories().cend())	//directory is ignored
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

	return (settings.outputDirectory / sourceFilePath.filename()).replace_extension(settings.generatedFilesExtension);
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
	GeneratedFile macrosDefinitionFile(settings.outputDirectory / settings.entityMacrosFilename);

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

	//Generate simple property rules macros + doc
	std::string macroDefinition;

	for (kodgen::SimplePropertyRule const* propertyRule : fileParserFactory.parsingSettings.propertyParsingSettings.simplePropertyRules)
	{
		macroDefinition = propertyRule->getMacroDefinition();

		if (!macroDefinition.empty())
		{
			macrosDefinitionFile.writeLines("",
											macroDefinition);
		}
	}

	//Generate complex property rules macros + doc
	for (kodgen::ComplexPropertyRule const* propertyRule : fileParserFactory.parsingSettings.propertyParsingSettings.complexPropertyRules)
	{
		macroDefinition = propertyRule->getMacroDefinition();

		if (!macroDefinition.empty())
		{
			macrosDefinitionFile.writeLines("",
											macroDefinition);
		}
	}

	macrosDefinitionFile.writeLine("\n#endif");
}

void FileGenerator::setupFileGenerationUnit(FileGenerationUnit& fileGenerationUnit) const noexcept
{
	fileGenerationUnit.logger		= logger;
	fileGenerationUnit._settings	= &settings;
}

void FileGenerator::loadToParseFiles(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> toParseFiles;
	
	TomlUtility::updateSetting(tomlGeneratorSettings, "toParseFiles", toParseFiles, logger);
	
	for (fs::path const& path : toParseFiles)
	{
		if (!settings.addToParseFile(path) && logger != nullptr)
		{
			logger->log("Can't add " + path.string() + " to the toParseFiles list as it doesn't exist, is not a file or is already part of the list.", ILogger::ELogSeverity::Warning);
		}
	}
}

void FileGenerator::loadToParseDirectories(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> toParseDirectories;

	TomlUtility::updateSetting(tomlGeneratorSettings, "toParseDirectories", toParseDirectories, logger);

	for (fs::path const& path : toParseDirectories)
	{
		if (!settings.addToParseDirectory(path) && logger != nullptr)
		{
			logger->log("Can't add " + path.string() + " to the toParseDirectories list as it doesn't exist, is not a directory or is already part of the list.", ILogger::ELogSeverity::Warning);
		}
	}
}

void FileGenerator::loadIgnoredFiles(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> ignoredFiles;

	TomlUtility::updateSetting(tomlGeneratorSettings, "ignoredFiles", ignoredFiles, logger);

	for (fs::path const& path : ignoredFiles)
	{
		if (!settings.addIgnoredFile(path) && logger != nullptr)
		{
			logger->log("Can't add " + path.string() + " to the ignoredFiles list as it doesn't exist, is not a file or is already part of the list.", ILogger::ELogSeverity::Warning);
		}
	}
}

void FileGenerator::loadIgnoredDirectories(toml::value const& tomlGeneratorSettings) noexcept
{
	std::unordered_set<fs::path, PathHash> ignoredDirectories;

	TomlUtility::updateSetting(tomlGeneratorSettings, "ignoredDirectories", ignoredDirectories, logger);

	for (fs::path const& path : ignoredDirectories)
	{
		if (!settings.addIgnoredDirectory(path) && logger != nullptr)
		{
			logger->log("Can't add " + path.string() + " to the ignoredDirectories list as it doesn't exist, is not a directory or is already part of the list.", ILogger::ELogSeverity::Warning);
		}
	}
}

bool FileGenerator::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value tomlContent = toml::parse(pathToSettingsFile.string());

		if (tomlContent.contains("FileGenerationSettings"))
		{
			toml::value const& tomlGeneratorSettings = toml::find(tomlContent, "FileGenerationSettings");

			TomlUtility::updateSetting(tomlGeneratorSettings, "generatedFilesExtension", settings.generatedFilesExtension, logger);
			TomlUtility::updateSetting(tomlGeneratorSettings, "entityMacrosFilename", settings.entityMacrosFilename, logger);
			TomlUtility::updateSetting(tomlGeneratorSettings, "supportedExtensions", settings.supportedExtensions, logger);
			TomlUtility::updateSetting(tomlGeneratorSettings, "outputDirectory", settings.outputDirectory, logger);

			loadToParseFiles(tomlGeneratorSettings);
			loadToParseDirectories(tomlGeneratorSettings);
			loadIgnoredFiles(tomlGeneratorSettings);
			loadIgnoredDirectories(tomlGeneratorSettings);
		}

		return true;
	}
	catch (std::runtime_error const&)
	{
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