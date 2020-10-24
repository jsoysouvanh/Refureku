#include "Kodgen/CodeGen/FileGenerationUnit.h"

#include "Kodgen/Properties/NativeProperties/NativeProperties.h"
#include "Kodgen/InfoStructures/NamespaceInfo.h"
#include "Kodgen/InfoStructures/StructClassInfo.h"
#include "Kodgen/InfoStructures/NestedStructClassInfo.h"
#include "Kodgen/InfoStructures/EnumInfo.h"
#include "Kodgen/InfoStructures/NestedEnumInfo.h"
#include "Kodgen/InfoStructures/EnumValueInfo.h"
#include "Kodgen/InfoStructures/VariableInfo.h"
#include "Kodgen/InfoStructures/FieldInfo.h"
#include "Kodgen/InfoStructures/FunctionInfo.h"
#include "Kodgen/InfoStructures/MethodInfo.h"

using namespace kodgen;

void FileGenerationUnit::generateFile(FileParsingResult const& parsingResult, FileGenerationResult& out_genResult) noexcept
{
	/**
	*	This constructor actually create the file in the filesystem.
	*	We create a file even if no entity was found so that we have the file generation timestamp to avoid
	*	parsing this file again if it hasn't changed.
	*/
	GeneratedFile generatedFile(makePathToGeneratedFile(parsingResult.parsedFile), parsingResult.parsedFile);

	preGenerateFile();

	writeFileContent(generatedFile, parsingResult, out_genResult);

	postGenerateFile();
}

void FileGenerationUnit::writeFileContent(GeneratedFile& generatedFile, FileParsingResult const& parsingResult, FileGenerationResult& out_genResult) noexcept
{
	//Header
	writeHeader(generatedFile, parsingResult);

	//Actual file content (per entity)
	for (NamespaceInfo const& namespaceInfo : parsingResult.namespaces)
	{
		if (!writeNamespaceToFile(generatedFile, namespaceInfo, out_genResult))
		{
			return;
		}
	}

	for (StructClassInfo const& structInfo : parsingResult.structs)
	{
		if (!writeStructOrClassToFile(generatedFile, structInfo, out_genResult))
		{
			return;
		}
	}

	for (StructClassInfo const& classInfo : parsingResult.classes)
	{
		if (!writeStructOrClassToFile(generatedFile, classInfo, out_genResult))
		{
			return;
		}
	}

	for (EnumInfo const& enumInfo : parsingResult.enums)
	{
		if (!writeEnumToFile(generatedFile, enumInfo, out_genResult))
		{
			return;
		}
	}

	for (VariableInfo const& variable : parsingResult.variables)
	{
		if (!writeVariableToFile(generatedFile, variable, out_genResult))
		{
			return;
		}
	}

	for (FunctionInfo const& function : parsingResult.functions)
	{
		if (!writeFunctionToFile(generatedFile, function, out_genResult))
		{
			return;
		}
	}

	//Footer
	writeFooter(generatedFile, parsingResult);
}

GeneratedCodeTemplate* FileGenerationUnit::getEntityGeneratedCodeTemplate(EntityInfo const& entityInfo) const noexcept
{
	GeneratedCodeTemplate* result = nullptr;

	//Find the specified code template
	decltype(entityInfo.properties.complexProperties)::const_iterator it = std::find_if(entityInfo.properties.complexProperties.cbegin(), entityInfo.properties.complexProperties.cend(),
																						[](ComplexProperty const& prop) { return prop.mainProperty == NativeProperties::generatedCodeTemplateProperty; });

	if (it == entityInfo.properties.complexProperties.cend())	//No main property corresponding to codeTemplateMainComplexPropertyName found
	{
		//Use this syntax to avoid changing anything if container type ever changes
		//Search for the default generated code template corresponding to this kind of entity
		decltype(_settings->_defaultGeneratedCodeTemplates)::const_iterator it2 = _settings->_defaultGeneratedCodeTemplates.find(entityInfo.entityType);

		if (it2 != _settings->_defaultGeneratedCodeTemplates.cend())
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
	else
	{
		std::string const& generatedCodeTemplateName = it->subProperties[0];

		//All these preconditions should have already been checked by the GenCodeTemplatePropertyRule during parsing
		assert(generatedCodeTemplateName.size() >= 2u && generatedCodeTemplateName.front() == '"' && generatedCodeTemplateName.back());

		//Again, this should have been checked by the GenCodeTemplatePropertyRule during parsing
		//substr remove start and end "
		assert(_settings->_generatedCodeTemplates.find(generatedCodeTemplateName.substr(1u, generatedCodeTemplateName.size() - 2u)) != _settings->_generatedCodeTemplates.cend());

		result = _settings->_generatedCodeTemplates.find(generatedCodeTemplateName.substr(1u, generatedCodeTemplateName.size() - 2u))->second;
	}

	return result;
}

bool FileGenerationUnit::writeEntityToFile(GeneratedFile& generatedFile, EntityInfo const& entityInfo, FileGenerationResult& out_genResult) noexcept
{
	GeneratedCodeTemplate*	codeTemplate			= getEntityGeneratedCodeTemplate(entityInfo);
	std::string				out_errorDescription;

	if (codeTemplate != nullptr)
	{
		codeTemplate->generateCode(generatedFile, entityInfo, *this, out_errorDescription);

		//Add an error to the result if something wrong happened during code generation
		if (!out_errorDescription.empty())
		{
			out_genResult.fileGenerationErrors.emplace_back(generatedFile.getPath(), entityInfo.getFullName(), out_errorDescription);

			return false;
		}
	}

	return true;
}

bool FileGenerationUnit::writeNamespaceToFile(GeneratedFile& generatedFile, EntityInfo const& namespaceInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(namespaceInfo.entityType == EEntityType::Namespace);

	//Write namespace
	writeEntityToFile(generatedFile, namespaceInfo, out_genResult);

	NamespaceInfo const& castNamespaceInfo = static_cast<NamespaceInfo const&>(namespaceInfo);

	//Write recursive namespaces
	for (NamespaceInfo const& nestedNamespaceInfo : castNamespaceInfo.namespaces)
	{
		if (!writeNamespaceToFile(generatedFile, nestedNamespaceInfo, out_genResult))
		{
			return false;
		}
	}

	//Write namespace structs
	for (StructClassInfo const& structInfo : castNamespaceInfo.structs)
	{
		if (!writeStructOrClassToFile(generatedFile, structInfo, out_genResult))
		{
			return false;
		}
	}

	//Write namespace classes
	for (StructClassInfo const& classInfo : castNamespaceInfo.classes)
	{
		if (!writeStructOrClassToFile(generatedFile, classInfo, out_genResult))
		{
			return false;
		}
	}

	//Write namespace enums
	for (EnumInfo const& enumInfo : castNamespaceInfo.enums)
	{
		if (!writeEnumToFile(generatedFile, enumInfo, out_genResult))
		{
			return false;
		}
	}

	//Write namespace variables
	for (VariableInfo const& varInfo : castNamespaceInfo.variables)
	{
		if (!writeVariableToFile(generatedFile, varInfo, out_genResult))
		{
			return false;
		}
	}

	//Write namespace functions
	for (FunctionInfo const& funcInfo : castNamespaceInfo.functions)
	{
		if (!writeFunctionToFile(generatedFile, funcInfo, out_genResult))
		{
			return false;
		}
	}

	return true;
}

bool FileGenerationUnit::writeStructOrClassToFile(GeneratedFile& generatedFile, EntityInfo const& structClassInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(structClassInfo.entityType == EEntityType::Struct || structClassInfo.entityType == EEntityType::Class);

	//Write struct/class
	writeEntityToFile(generatedFile, structClassInfo, out_genResult);

	StructClassInfo const& castStructClassInfo = static_cast<StructClassInfo const&>(structClassInfo);

	//Write struct/class nested structs
	for (std::shared_ptr<NestedStructClassInfo> const& nestedStructInfo : castStructClassInfo.nestedStructs)
	{
		if (!writeNestedStructOrClassToFile(generatedFile, *nestedStructInfo, out_genResult))
		{
			return false;
		}
	}

	//Write struct/class nested classes
	for (std::shared_ptr<NestedStructClassInfo> const& nestedClassInfo : castStructClassInfo.nestedClasses)
	{
		if (!writeNestedStructOrClassToFile(generatedFile, *nestedClassInfo, out_genResult))
		{
			return false;
		}
	}

	//Write class nested enums
	for (NestedEnumInfo const& nestedEnumInfo : castStructClassInfo.nestedEnums)
	{
		if (!writeEnumToFile(generatedFile, nestedEnumInfo, out_genResult))
		{
			return false;
		}
	}

	//Write class fields
	for (FieldInfo const& fieldInfo : castStructClassInfo.fields)
	{
		if (!writeFieldToFile(generatedFile, fieldInfo, out_genResult))
		{
			return false;
		}
	}

	//Write class methods
	for (MethodInfo const& methodInfo : castStructClassInfo.methods)
	{
		if (!writeMethodToFile(generatedFile, methodInfo, out_genResult))
		{
			return false;
		}
	}

	return true;
}

bool FileGenerationUnit::writeNestedStructOrClassToFile(GeneratedFile& generatedFile, EntityInfo const& nestedStructClassInfo, FileGenerationResult& out_genResult) noexcept
{
	//Might do something else special for nested structs/classes in the future
	return writeStructOrClassToFile(generatedFile, nestedStructClassInfo, out_genResult);
}

bool FileGenerationUnit::writeEnumToFile(GeneratedFile& generatedFile, EntityInfo const& enumInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(enumInfo.entityType == EEntityType::Enum);

	//Write enum
	if (!writeEntityToFile(generatedFile, enumInfo, out_genResult))
	{
		return false;
	}

	EnumInfo const& castEnumInfo = static_cast<EnumInfo const&>(enumInfo);

	//Write enum values
	for (EnumValueInfo const& enumValueInfo : castEnumInfo.enumValues)
	{
		if (!writeEnumValueToFile(generatedFile, enumValueInfo, out_genResult))
		{
			return false;
		}
	}

	return true;
}

bool FileGenerationUnit::writeEnumValueToFile(GeneratedFile& generatedFile, EntityInfo const& enumValueInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(enumValueInfo.entityType == EEntityType::EnumValue);

	return writeEntityToFile(generatedFile, enumValueInfo, out_genResult);
}

bool FileGenerationUnit::writeVariableToFile(GeneratedFile& generatedFile, EntityInfo const& variableInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(variableInfo.entityType == EEntityType::Variable);

	return writeEntityToFile(generatedFile, variableInfo, out_genResult);
}

bool FileGenerationUnit::writeFieldToFile(GeneratedFile& generatedFile, EntityInfo const& fieldInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(fieldInfo.entityType == EEntityType::Field);

	return writeEntityToFile(generatedFile, fieldInfo, out_genResult);
}

bool FileGenerationUnit::writeFunctionToFile(GeneratedFile& generatedFile, EntityInfo const& functionInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(functionInfo.entityType == EEntityType::Function);

	return writeEntityToFile(generatedFile, functionInfo, out_genResult);
}

bool FileGenerationUnit::writeMethodToFile(GeneratedFile& generatedFile, EntityInfo const& methodInfo, FileGenerationResult& out_genResult) noexcept
{
	assert(methodInfo.entityType == EEntityType::Method);

	return writeEntityToFile(generatedFile, methodInfo, out_genResult);
}

bool FileGenerationUnit::shouldRegenerateFile(fs::path const& filePath) const noexcept
{
	fs::path pathToGeneratedFile = makePathToGeneratedFile(filePath);

	return !fs::exists(pathToGeneratedFile) || fs::last_write_time(filePath) > fs::last_write_time(pathToGeneratedFile);
}

fs::path FileGenerationUnit::makePathToGeneratedFile(fs::path const& sourceFilePath) const noexcept
{
	assert(fs::exists(sourceFilePath) && fs::is_regular_file(sourceFilePath));

	return (_settings->getOutputDirectory() / sourceFilePath.filename()).replace_extension(_settings->generatedFilesExtension);
}

void FileGenerationUnit::preGenerateFile() noexcept
{
	//Default implementation does nothing
}

void FileGenerationUnit::postGenerateFile() noexcept
{
	//Default implementation does nothing
}

void FileGenerationUnit::writeHeader(GeneratedFile& file, FileParsingResult const&) const noexcept
{
	file.writeLine("#pragma once\n");

	file.writeLines("/**", "*	Source file: " + file.getSourceFilePath().string(), "*/\n");

	file.writeLine("#include \"" + _settings->entityMacrosFilename + "\"\n");
}

void FileGenerationUnit::writeFooter(GeneratedFile&, FileParsingResult const&) const noexcept
{
	//Default implementation has no footer
}