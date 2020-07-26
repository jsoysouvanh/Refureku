#include "CodeGen/FileGenerator.h"

#include <cassert>

#include "InfoStructures/NamespaceInfo.h"
#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/NestedStructClassInfo.h"
#include "InfoStructures/EnumInfo.h"
#include "InfoStructures/NestedEnumInfo.h"
#include "InfoStructures/EnumValueInfo.h"
#include "InfoStructures/FieldInfo.h"
#include "InfoStructures/MethodInfo.h"
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

void FileGenerator::generateFile(FileGenerationResult& genResult, FileParsingResult const& parsingResult) noexcept
{
	/**
	*	This constructor actually create the file in the filesystem.
	*	We create a file even if no entity was found so that we have the file generation timestamp to avoid
	*	parsing this file again if it hasn't changed.
	*/
	GeneratedFile generatedFile(makePathToGeneratedFile(parsingResult.parsedFile), parsingResult.parsedFile);

	preGenerateFile();

	//Header
	writeHeader(generatedFile, parsingResult);

	//Actual file content (per entity)
	for (NamespaceInfo const& namespaceInfo : parsingResult.namespaces)
	{
		writeNamespaceToFile(generatedFile, namespaceInfo, genResult);
	}

	for (StructClassInfo const& structInfo : parsingResult.structs)
	{
		writeStructOrClassToFile(generatedFile, structInfo, genResult);
	}

	for (StructClassInfo const& classInfo : parsingResult.classes)
	{
		writeStructOrClassToFile(generatedFile, classInfo, genResult);
	}

	for (EnumInfo const& enumInfo : parsingResult.enums)
	{
		writeEnumToFile(generatedFile, enumInfo, genResult);
	}

	/**
	*	TODO
	*
	*	for (FieldInfo const& fieldInfo : parsingResult.fields)
	*	{
	*		writeFieldToFile(generatedFile, fieldInfo, genResult);
	*	}
	*
	*	for (MethodInfo const& methodInfo : parsingResult.functions)
	*	{
	*		writeMethodToFile(generatedFile, methodInfo, genResult);
	*	}
	*/

	//Footer
	writeFooter(generatedFile, parsingResult);

	postGenerateFile();
}

GeneratedCodeTemplate* FileGenerator::getEntityGeneratedCodeTemplate(EntityInfo const& entityInfo, EFileGenerationError& out_error) const noexcept
{
	GeneratedCodeTemplate* result = nullptr;

	//Find the specified code template
	decltype(entityInfo.properties.complexProperties)::const_iterator it = std::find_if(entityInfo.properties.complexProperties.cbegin(), entityInfo.properties.complexProperties.cend(),
																			[this](ComplexProperty const& prop) { return prop.name == codeTemplateMainComplexPropertyName; });

	if (it == entityInfo.properties.complexProperties.cend())	//No main property corresponding to codeTemplateMainComplexPropertyName found
	{
		//Search for the default generated code template corresponding to this kind of entity
		decltype(_defaultGeneratedCodeTemplates)::const_iterator it2 = _defaultGeneratedCodeTemplates.find(entityInfo.entityType);

		if (it2 != _defaultGeneratedCodeTemplates.cend())
		{
			//We found a default generated code template!
			result = it2->second;
		}
		else
		{
			//Didn't find a default generated code template, generate no code for this entity
			return nullptr;
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

void FileGenerator::writeEntityToFile(GeneratedFile& generatedFile, EntityInfo const& entityInfo, FileGenerationResult& genResult) noexcept
{
	EFileGenerationError	error			= EFileGenerationError::Count;
	GeneratedCodeTemplate*	codeTemplate	= getEntityGeneratedCodeTemplate(entityInfo, error);

	if (codeTemplate != nullptr)
	{
		codeTemplate->generateCode(generatedFile, entityInfo);
	}
	else if (error != EFileGenerationError::Count)
	{
		genResult.fileGenerationErrors.emplace_back(FileGenerationError(generatedFile.getSourceFilePath(), entityInfo.name, error));
	}
}

void FileGenerator::writeNamespaceToFile(GeneratedFile& generatedFile, EntityInfo const& namespaceInfo, FileGenerationResult& genResult) noexcept
{
	assert(namespaceInfo.entityType == EntityInfo::EType::Namespace);

	//Write namespace
	writeEntityToFile(generatedFile, namespaceInfo, genResult);

	NamespaceInfo const& castNamespaceInfo = static_cast<NamespaceInfo const&>(namespaceInfo);
	
	//Write recursive namespaces
	for (NamespaceInfo const& nestedNamespaceInfo : castNamespaceInfo.namespaces)
	{
		writeNamespaceToFile(generatedFile, nestedNamespaceInfo, genResult);
	}

	//Write namespace structs
	for (StructClassInfo const& structInfo : castNamespaceInfo.structs)
	{
		writeStructOrClassToFile(generatedFile, structInfo, genResult);
	}

	//Write namespace classes
	for (StructClassInfo const& classInfo : castNamespaceInfo.classes)
	{
		writeStructOrClassToFile(generatedFile, classInfo, genResult);
	}

	//Write namespace enums
	for (EnumInfo const& enumInfo : castNamespaceInfo.enums)
	{
		writeEnumToFile(generatedFile, enumInfo, genResult);
	}

	/**
	*	TODO
	*
	*	for (FieldInfo const& fieldInfo : castNamespaceInfo.fields)
	*	{
	*		writeFieldToFile(generatedFile, fieldInfo, genResult);
	*	}
	*
	*	for (MethodInfo const& methodInfo : castNamespaceInfo.functions)
	*	{
	*		writeMethodToFile(generatedFile, methodInfo, genResult);
	*	}
	*/
}

void FileGenerator::writeStructOrClassToFile(GeneratedFile& generatedFile, EntityInfo const& structClassInfo, FileGenerationResult& genResult) noexcept
{
	assert(structClassInfo.entityType == EntityInfo::EType::Struct || structClassInfo.entityType == EntityInfo::EType::Class);

	//Write struct/class
	writeEntityToFile(generatedFile, structClassInfo, genResult);

	StructClassInfo const& castStructClassInfo = static_cast<StructClassInfo const&>(structClassInfo);

	//Write struct/class nested structs
	for (std::shared_ptr<NestedStructClassInfo> const& nestedStructInfo : castStructClassInfo.nestedStructs)
	{
		writeNestedStructOrClassToFile(generatedFile, *nestedStructInfo, genResult);
	}

	//Write struct/class nested classes
	for (std::shared_ptr<NestedStructClassInfo> const& nestedClassInfo : castStructClassInfo.nestedClasses)
	{
		writeNestedStructOrClassToFile(generatedFile, *nestedClassInfo, genResult);
	}

	//Write class nested enums
	for (NestedEnumInfo const& nestedEnumInfo : castStructClassInfo.nestedEnums)
	{
		writeEnumToFile(generatedFile, nestedEnumInfo, genResult);
	}

	//Write class fields
	for (FieldInfo const& fieldInfo : castStructClassInfo.fields)
	{
		writeFieldToFile(generatedFile, fieldInfo, genResult);
	}
	
	//Write class methods
	for (MethodInfo const& methodInfo : castStructClassInfo.methods)
	{
		writeMethodToFile(generatedFile, methodInfo, genResult);
	}
}

void FileGenerator::writeNestedStructOrClassToFile(GeneratedFile& generatedFile, EntityInfo const& nestedStructClassInfo, FileGenerationResult& genResult) noexcept
{
	//Might do something else special for nested structs/classes in the future
	writeStructOrClassToFile(generatedFile, nestedStructClassInfo, genResult);
}

void FileGenerator::writeEnumToFile(GeneratedFile& generatedFile, EntityInfo const& enumInfo, FileGenerationResult& genResult) noexcept
{
	assert(enumInfo.entityType == EntityInfo::EType::Enum);

	//Write enum
	writeEntityToFile(generatedFile, enumInfo, genResult);

	EnumInfo const& castEnumInfo = static_cast<EnumInfo const&>(enumInfo);

	//Write enum values
	for (EnumValueInfo const& enumValueInfo : castEnumInfo.enumValues)
	{
		writeEnumValueToFile(generatedFile, enumValueInfo, genResult);
	}
}

void FileGenerator::writeEnumValueToFile(GeneratedFile& generatedFile, EntityInfo const& enumValueInfo, FileGenerationResult& genResult) noexcept
{
	assert(enumValueInfo.entityType == EntityInfo::EType::EnumValue);

	writeEntityToFile(generatedFile, enumValueInfo, genResult);
}

void FileGenerator::writeFieldToFile(GeneratedFile& generatedFile, EntityInfo const& fieldInfo, FileGenerationResult& genResult) noexcept
{
	assert(fieldInfo.entityType == EntityInfo::EType::Field);

	writeEntityToFile(generatedFile, fieldInfo, genResult);
}

void FileGenerator::writeMethodToFile(GeneratedFile& generatedFile, EntityInfo const& methodInfo, FileGenerationResult& genResult) noexcept
{
	assert(methodInfo.entityType == EntityInfo::EType::Method);

	writeEntityToFile(generatedFile, methodInfo, genResult);
}

bool FileGenerator::shouldRegenerateFile(fs::path const& filePath) const noexcept
{
	fs::path pathToGeneratedFile = makePathToGeneratedFile(filePath);

	return !fs::exists(pathToGeneratedFile) || fs::last_write_time(filePath) > fs::last_write_time(pathToGeneratedFile);
}

fs::path FileGenerator::makePathToGeneratedFile(fs::path const& sourceFilePath) const noexcept
{
	assert(fs::exists(sourceFilePath) && fs::is_regular_file(sourceFilePath));

	return (outputDirectory / sourceFilePath.filename()).replace_extension(generatedFilesExtension);
}

void FileGenerator::preGenerateFile() noexcept
{
	//Default implementation does nothing
}

void FileGenerator::postGenerateFile() noexcept
{
	//Default implementation does nothing
}

void FileGenerator::writeHeader(GeneratedFile& file, FileParsingResult const&) const noexcept
{
	file.writeLine("#pragma once\n");

	file.writeLines("/**", "*	Source file: " + file.getSourceFilePath().string(), "*/\n");

	file.writeLine("#include \"" + _entityMacrosDefFilename + "\"\n");
}

void FileGenerator::writeFooter(GeneratedFile&, FileParsingResult const&) const noexcept
{
	//Default implementation has no footer
}

void FileGenerator::addGeneratedCodeTemplate(std::string const& templateName, GeneratedCodeTemplate* codeTemplate) noexcept
{
	if (codeTemplate != nullptr)
	{
		_generatedCodeTemplates[templateName] = codeTemplate;

		updateSupportedCodeTemplateRegex();
	}
}

bool FileGenerator::setDefaultGeneratedCodeTemplate(EntityInfo::EType entityType, std::string const& templateName) noexcept
{
	decltype(_generatedCodeTemplates)::const_iterator it = _generatedCodeTemplates.find(templateName);

	if (it != _generatedCodeTemplates.cend())
	{
		_defaultGeneratedCodeTemplates[entityType] = it->second;

		return true;
	}

	return false;
}

void FileGenerator::processFile(FileParser& parser, FileGenerationResult& genResult, fs::path const& pathToFile) noexcept
{
	FileParsingResult parsingResult;

	genResult.parsedFiles.push_back(pathToFile);

	//Parse file
	if (parser.parse(pathToFile, parsingResult))
	{
		//Generate file according to parsing result
		generateFile(genResult, parsingResult);
	}
	else
	{
		//Transfer parsing errors into the file generation result
		genResult.parsingErrors.insert(genResult.parsingErrors.cend(), std::make_move_iterator(parsingResult.errors.cbegin()), std::make_move_iterator(parsingResult.errors.cend()));
	}
}

void FileGenerator::processIncludedFiles(FileParser& parser, FileGenerationResult& genResult, bool forceRegenerateAll) noexcept
{
	for (fs::path path : toParseFiles)
	{
		if (fs::exists(path) && !fs::is_directory(path))
		{
			if (forceRegenerateAll || shouldRegenerateFile(path))
			{
				processFile(parser, genResult, path);
			}
			else
			{
				genResult.upToDateFiles.push_back(path);
			}
		}
		else
		{
			//TODO: Add FileGenerationFile invalid path
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
							ignoredFiles.find(entryPath.string()) == ignoredFiles.cend())
						{
							if (forceRegenerateAll || shouldRegenerateFile(entryPath))
							{
								processFile(parser, genResult, entryPath);
							}
							else
							{
								genResult.upToDateFiles.push_back(entryPath);
							}
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

	PropertyParsingSettings& pps = parser.parsingSettings.propertyParsingSettings;

	//Define empty entity macros to allow compilation outside of the Kodgen parsing
	macrosDefinitionFile.writeLines("#pragma once",
									"",
									"#ifndef " + parser.parsingMacro,
									"	#define " + pps.namespacePropertyRules.macroName + "(...)",
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

	if (outputDirectory.empty())
	{
		if (logger != nullptr)
		{
			genResult.fileGenerationErrors.emplace_back(FileGenerationError("", "", EFileGenerationError::UnspecifiedOutputDirectory));

			logger->log("Output directory is empty, it must be specified for the files to be generated.", ILogger::ELogSeverity::Error);
		}
	}
	else
	{
		//Before doing anything, make sure destination folder exists
		if (!fs::exists(outputDirectory))
		{
			//Try to create them is it doesn't exist
			try
			{
				genResult.completed = fs::create_directories(outputDirectory);
			}
			catch (fs::filesystem_error const& exception)
			{
				if (logger != nullptr)
				{
					genResult.fileGenerationErrors.emplace_back(FileGenerationError("", "", EFileGenerationError::InvalidOutputDirectory));

					logger->log("Output directory is invalid: " + std::string(exception.what()), ILogger::ELogSeverity::Error);
				}
			}
		}

		if (fs::is_directory(outputDirectory))
		{
			refreshPropertyRules(parser.parsingSettings);

			generateMacrosFile(parser);

			processIncludedFiles(parser, genResult, forceRegenerateAll);
			processIncludedDirectories(parser, genResult, forceRegenerateAll);

			genResult.completed = true;
		}
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
		if (logger != nullptr)
		{
			logger->log("Syntax error in settings file.\n" + std::string(e.what()), ILogger::ELogSeverity::Error);
		}
	}
	
	return false;
}