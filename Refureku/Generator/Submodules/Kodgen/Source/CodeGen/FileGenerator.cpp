#include "CodeGen/FileGenerator.h"

#include <assert.h>

#include "Misc/TomlUtility.h"

using namespace kodgen;

FileGenerator::FileGenerator() noexcept
{
}

FileGenerator::~FileGenerator() noexcept
{
	for (auto& [key, value] : _generatedCodeTemplates)
	{
		delete value;
	}
}

void FileGenerator::updateSupportedCodeTemplateRegex() noexcept
{
	_supportedCodeTemplateRegex.clear();

	for (auto& [key, value] : _generatedCodeTemplates)
	{
		_supportedCodeTemplateRegex += key + "|";
	}

	_supportedCodeTemplateRegex.pop_back();
}

void FileGenerator::generateEntityFile(FileGenerationResult& genResult, fs::path const& filePath, ParsingResult const& parsingResult) noexcept
{
	GeneratedFile generatedFile(makePathToGeneratedFile(filePath), filePath);

	//Header
	writeHeader(generatedFile, parsingResult);

	//Actual file content (per entity)
	for (StructClassInfo structOrClassInfo : parsingResult.classes)
	{
		writeEntityToFile(generatedFile, structOrClassInfo, genResult);
	}

	for (StructClassInfo structOrClassInfo : parsingResult.structs)
	{
		writeEntityToFile(generatedFile, structOrClassInfo, genResult);
	}

	for (EnumInfo enumInfo : parsingResult.enums)
	{
		writeEntityToFile(generatedFile, enumInfo, genResult);
	}

	//Footer
	writeFooter(generatedFile, parsingResult);
}

GeneratedCodeTemplate* FileGenerator::getEntityGeneratedCodeTemplate(EntityInfo& entityInfo, EFileGenerationError& out_error) const noexcept
{
	GeneratedCodeTemplate* result = nullptr;

	//Find the specified code template
	decltype(entityInfo.properties.complexProperties)::const_iterator it = std::find_if(entityInfo.properties.complexProperties.cbegin(), entityInfo.properties.complexProperties.cend(),
																			[this](ComplexProperty const& prop) { return prop.name == codeTemplateMainComplexPropertyName; });

	if (it == entityInfo.properties.complexProperties.cend())	//No main property corresponding to codeTemplateMainComplexPropertyName found
	{
		if (entityInfo.entityType == EntityInfo::EType::Class)
		{
			if (_defaultClassTemplate != nullptr)
			{
				result = _defaultClassTemplate;
			}
			else
			{
				out_error = EFileGenerationError::MissingGeneratedCodeTemplateComplexProperty;
			}
		}
		else if (entityInfo.entityType == EntityInfo::EType::Struct)
		{
			if (_defaultStructTemplate != nullptr)
			{
				result = _defaultStructTemplate;
			}
			else
			{
				out_error = EFileGenerationError::MissingGeneratedCodeTemplateComplexProperty;
			}
		}
		else	//isEnum
		{
			if (_defaultEnumTemplate != nullptr)
			{
				result = _defaultEnumTemplate;
			}
			else
			{
				out_error = EFileGenerationError::MissingGeneratedCodeTemplateComplexProperty;
			}
		}
	}
	else if (it->subProperties.empty())	//No sub prop provided to the codeTemplateMainComplexPropertyName main prop
	{
		out_error = EFileGenerationError::NoGeneratedCodeTemplateProvided;
	}
	else if (it->subProperties.size() > 1)	//More than one prop provided to the codeTemplateMainComplexPropertyName main prop
	{
		out_error = EFileGenerationError::TooManyGeneratedCodeTemplateProvided;
	}
	else
	{
		std::unordered_map<std::string,	GeneratedCodeTemplate*>::const_iterator it2 = _generatedCodeTemplates.find(it->subProperties[0]);

		if (it2 != _generatedCodeTemplates.cend())
		{
			result = it2->second;
		}
		else
		{
			out_error = EFileGenerationError::UnregisteredGeneratedCodeTemplateProvided;
		}
	}

	//make sure an error is set if we have no result
	assert(result != nullptr || out_error != EFileGenerationError::Count);

	return result;
}

void FileGenerator::writeEntityToFile(GeneratedFile& generatedFile, EntityInfo& entityInfo, FileGenerationResult& genResult) noexcept
{
	EFileGenerationError error = EFileGenerationError::Count;
	GeneratedCodeTemplate* codeTemplate = getEntityGeneratedCodeTemplate(entityInfo, error);

	if (codeTemplate != nullptr)
	{
		codeTemplate->generateCode(generatedFile, entityInfo);
	}
	else
	{
		genResult.fileGenerationErrors.emplace_back(FileGenerationError(generatedFile.getSourceFilePath(), entityInfo.name, error));
	}
}

bool FileGenerator::shouldRegenerateFile(fs::path const& filePath) const noexcept
{
	fs::path pathToGeneratedFile = makePathToGeneratedFile(filePath);

	return !fs::exists(pathToGeneratedFile) || fs::last_write_time(filePath) > fs::last_write_time(pathToGeneratedFile);
}

fs::path FileGenerator::makePathToGeneratedFile(fs::path const& sourceFilePath) const noexcept
{
	return (outputDirectory / sourceFilePath.filename()).replace_extension(generatedFilesExtension);
}

void FileGenerator::writeHeader(GeneratedFile& file, ParsingResult const&) const noexcept
{
	file.writeLine("#pragma once\n");

	file.writeLines("/**", "*	Source file: " + file.getSourceFilePath().string(), "*/\n");

	file.writeLine("#include \"" + _entityMacrosDefFilename + "\"\n");
}

void FileGenerator::writeFooter(GeneratedFile&, ParsingResult const&) const noexcept
{
	//Default implementation has no footer
}

void FileGenerator::addGeneratedCodeTemplate(std::string const& templateName, GeneratedCodeTemplate* codeTemplate, bool setAsDefaultClassTemplate) noexcept
{
	if (codeTemplate != nullptr)
	{
		_generatedCodeTemplates[templateName] = codeTemplate;

		updateSupportedCodeTemplateRegex();

		if (setAsDefaultClassTemplate)
			_defaultClassTemplate = codeTemplate;
	}
}

bool FileGenerator::setDefaultClassTemplate(std::string const& templateName) noexcept
{
	decltype(_generatedCodeTemplates)::const_iterator it = _generatedCodeTemplates.find(templateName);

	if (it != _generatedCodeTemplates.cend())
	{
		_defaultClassTemplate = it->second;
		
		return true;
	}

	return false;
}

bool FileGenerator::setDefaultStructTemplate(std::string const& templateName) noexcept
{
	decltype(_generatedCodeTemplates)::const_iterator it = _generatedCodeTemplates.find(templateName);

	if (it != _generatedCodeTemplates.cend())
	{
		_defaultStructTemplate = it->second;

		return true;
	}

	return false;
}

bool FileGenerator::setDefaultEnumTemplate(std::string const& templateName) noexcept
{
	decltype(_generatedCodeTemplates)::const_iterator it = _generatedCodeTemplates.find(templateName);

	if (it != _generatedCodeTemplates.cend())
	{
		_defaultEnumTemplate = it->second;

		return true;
	}

	return false;
}

void FileGenerator::processFile(FileParser& parser, FileGenerationResult& genResult, fs::path const& pathToFile) noexcept
{
	//Parse file
	ParsingResult parsingResult;

	if (parser.parse(pathToFile, parsingResult))
	{
		generateEntityFile(genResult, pathToFile, parsingResult);
	}
	else
	{
		//Transfer parsing errors into the file generation result
		genResult.parsingErrors.insert(genResult.parsingErrors.end(), std::make_move_iterator(parsingResult.parsingErrors.begin()), std::make_move_iterator(parsingResult.parsingErrors.end()));
	}
}

void FileGenerator::processIncludedFiles(FileParser& parser, FileGenerationResult& genResult, bool forceRegenerateAll) noexcept
{
	for (fs::path path : toParseFiles)
	{
		if (fs::exists(path) &&
			!fs::is_directory(path) &&
			(forceRegenerateAll || shouldRegenerateFile(path)))
		{
			processFile(parser, genResult, path);
		}
	}
}

void FileGenerator::processIncludedDirectories(FileParser& parser, FileGenerationResult& genResult, bool forceRegenerateAll) noexcept
{
	for (fs::path pathToIncludedDir : toParseDirectories)
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
						if (supportedExtensions.find(entryPath.extension().string()) != supportedExtensions.cend() &&
							ignoredFiles.find(entryPath.string()) == ignoredFiles.cend() &&
							(forceRegenerateAll || shouldRegenerateFile(entryPath)))
						{
							processFile(parser, genResult, entryPath);
						}
					}
					else if (entry.is_directory() && ignoredDirectories.find(entryPath.string()) != ignoredDirectories.cend())
					{
						//Don't iterate on ignored directory content
						directoryIt.disable_recursion_pending();
					}
				}
			}
		}
	}
}

void FileGenerator::refreshPropertyRules(ParsingSettings& parsingSettings) const noexcept
{
	//Make sure the CodeTemplate property is setup in class, struct and enum
	parsingSettings.propertyParsingSettings.classPropertyRules.removeComplexPropertyRule(std::string(codeTemplateMainComplexPropertyName));
	parsingSettings.propertyParsingSettings.classPropertyRules.addComplexPropertyRule(std::string(codeTemplateMainComplexPropertyName), std::string(_supportedCodeTemplateRegex));

	parsingSettings.propertyParsingSettings.structPropertyRules.removeComplexPropertyRule(std::string(codeTemplateMainComplexPropertyName));
	parsingSettings.propertyParsingSettings.structPropertyRules.addComplexPropertyRule(std::string(codeTemplateMainComplexPropertyName), std::string(_supportedCodeTemplateRegex));

	parsingSettings.propertyParsingSettings.enumPropertyRules.removeComplexPropertyRule(std::string(codeTemplateMainComplexPropertyName));
	parsingSettings.propertyParsingSettings.enumPropertyRules.addComplexPropertyRule(std::string(codeTemplateMainComplexPropertyName), std::string(_supportedCodeTemplateRegex));
}

void FileGenerator::generateMacrosFile(FileParser& parser) const noexcept
{
	GeneratedFile macrosDefinitionFile(outputDirectory / _entityMacrosDefFilename);

	PropertyParsingSettings& pps = parser.getParsingSettings().propertyParsingSettings;

	//Define empty entity macros to allow compilation outside of the Kodgen parsing
	macrosDefinitionFile.writeLines("#pragma once",
									"",
									"#ifndef " + parser.getParsingMacro(),
									"	#define " + pps.classPropertyRules.macroName + "(...)",
									"	#define " + pps.structPropertyRules.macroName + "(...)",
									"	#define " + pps.fieldPropertyRules.macroName + "(...)",
									"	#define " + pps.methodPropertyRules.macroName + "(...)",
									"	#define " + pps.enumPropertyRules.macroName + "(...)",
									"	#define " + pps.enumValuePropertyRules.macroName + "(...)",
									"#endif");
}

FileGenerationResult FileGenerator::generateFiles(FileParser& parser, bool forceRegenerateAll) noexcept
{
	FileGenerationResult genResult;

	//Before doing anything, make sure destination folder exists
	if (!fs::exists(outputDirectory))
	{
		try
		{
			genResult.completed = fs::create_directories(outputDirectory);
		}
		catch (fs::filesystem_error const& e)
		{
			std::cerr << "Output directory is invalid: " << e.what() << std::endl;
		}
	}

	if (fs::is_directory(outputDirectory))
	{
		ParsingSettings& parsingSettings = parser.getParsingSettings();

		refreshPropertyRules(parsingSettings);

		generateMacrosFile(parser);

		processIncludedFiles(parser, genResult, forceRegenerateAll);
		processIncludedDirectories(parser, genResult, forceRegenerateAll);

		genResult.completed = true;
	}
	
	return genResult;
}

bool FileGenerator::loadSettings(fs::path const& pathToSettingsFile) noexcept
{
	try
	{
		toml::value settings = toml::parse(pathToSettingsFile.string());

		if (settings.contains("FileGeneratorSettings"))
		{
			toml::value const& generatorSettings = toml::find(settings, "FileGeneratorSettings");

			TomlUtility::updateSetting<std::string>(generatorSettings, "codeTemplateMainComplexPropertyName", codeTemplateMainComplexPropertyName);
			TomlUtility::updateSetting<std::string>(generatorSettings, "generatedFilesExtension", generatedFilesExtension);
			TomlUtility::updateSetting<fs::path>(generatorSettings, "outputDirectory", outputDirectory);
			TomlUtility::updateSetting(generatorSettings, "toParseFiles", toParseFiles);
			TomlUtility::updateSetting(generatorSettings, "toParseDirectories", toParseDirectories);
			TomlUtility::updateSetting(generatorSettings, "ignoredFiles", ignoredFiles);
			TomlUtility::updateSetting(generatorSettings, "ignoredDirectories", ignoredDirectories);
			TomlUtility::updateSetting(generatorSettings, "supportedExtensions", supportedExtensions);
		}

		return true;
	}
	catch (std::runtime_error const&)
	{
	}
	catch (toml::syntax_error const& e)
	{
		std::cerr << "Syntax error in settings file." << std::endl <<
			e.what() << std::endl;
	}
	
	return false;
}