#include "Kodgen/CodeGen/FileGenerator.h"

using namespace kodgen;

std::set<fs::path> FileGenerator::identifyFilesToProcess(FileGenerationResult& out_genResult, bool forceRegenerateAll) const noexcept
{
	std::set<fs::path> result;

	//Iterate over all "toParseFiles"
	for (fs::path path : settings.toParseFiles)
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
			//TODO: Add FileGenerationFile invalid path
			logger->log("File " + path.string() + " doesn't exist", ILogger::ELogSeverity::Warning);
		}
	}

	//Iterate over all "toParseDirectories"
	for (fs::path pathToIncludedDir : settings.toParseDirectories)
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
						if (settings.supportedExtensions.find(entryPath.extension().string()) != settings.supportedExtensions.cend() &&
							settings.ignoredFiles.find(entryPath.string()) == settings.ignoredFiles.cend())
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
					else if (entry.is_directory() && settings.ignoredDirectories.find(entryPath.string()) != settings.ignoredDirectories.cend())
					{
						//Don't iterate on ignored directory content
						directoryIt.disable_recursion_pending();
					}
				}
			}
		}
		else
		{
			//TODO: Add FileGenerationFile invalid path
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

void FileGenerator::addNativePropertyRules(PropertyParsingSettings& propParsingSettings) noexcept
{
	propParsingSettings.simplePropertyRules.push_back(&_parseAllNestedPropertyRule);
	propParsingSettings.complexPropertyRules.push_back(&_generatedCodeTemplatePropertyRule);
}

void FileGenerator::clearNativePropertyRules(PropertyParsingSettings& propParsingSettings) noexcept
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
											propertyRule->getMacroDefinition());
		}
	}

	//Generate complex property rules macros + doc
	for (kodgen::ComplexPropertyRule const* propertyRule : fileParserFactory.parsingSettings.propertyParsingSettings.complexPropertyRules)
	{
		macroDefinition = propertyRule->getMacroDefinition();

		if (!macroDefinition.empty())
		{
			macrosDefinitionFile.writeLines("",
											propertyRule->getMacroDefinition());
		}
	}

	macrosDefinitionFile.writeLine("\n#endif");
}

void FileGenerator::setupFileGenerationUnit(FileGenerationUnit& fileGenerationUnit) const noexcept
{
	fileGenerationUnit.logger		= logger;
	fileGenerationUnit._settings	= &settings;
}

bool FileGenerator::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value tomlContent = toml::parse(pathToSettingsFile.string());

		if (tomlContent.contains("FileGenerationSettings"))
		{
			toml::value const& generatorSettings = toml::find(tomlContent, "FileGenerationSettings");

			TomlUtility::updateSetting<std::string>(generatorSettings, "generatedFilesExtension", settings.generatedFilesExtension);
			TomlUtility::updateSetting<fs::path>(generatorSettings, "outputDirectory", settings.outputDirectory);
			TomlUtility::updateSetting<std::string>(generatorSettings, "entityMacrosFilename", settings.entityMacrosFilename);
			TomlUtility::updateSetting(generatorSettings, "toParseFiles", settings.toParseFiles);
			TomlUtility::updateSetting(generatorSettings, "toParseDirectories", settings.toParseDirectories);
			TomlUtility::updateSetting(generatorSettings, "ignoredFiles", settings.ignoredFiles);
			TomlUtility::updateSetting(generatorSettings, "ignoredDirectories", settings.ignoredDirectories);
			TomlUtility::updateSetting(generatorSettings, "supportedExtensions", settings.supportedExtensions);
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