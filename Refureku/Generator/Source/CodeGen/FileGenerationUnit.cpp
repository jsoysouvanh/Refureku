#include "RefurekuGenerator/CodeGen/FileGenerationUnit.h"

using namespace rfk;

std::string const				FileGenerationUnit::_endFileMacroName = "File_GENERATED";
std::hash<std::string> const	FileGenerationUnit::_stringHasher;

void FileGenerationUnit::postGenerateFile() noexcept
{
	_generatedNamespaces.clear();
	_generatedClasses.clear();
	_generatedEnums.clear();
	_generatedVariables.clear();
	_generatedFunctions.clear();
}

void FileGenerationUnit::writeHeader(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerationUnit::writeHeader(file, parsingResult);

	file.writeLines("#include <Refureku/TypeInfo/Namespaces/Namespace.h>",
					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>",
					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>",
					"#include <Refureku/TypeInfo/Archetypes/Class.h>",
					"#include <Refureku/TypeInfo/Archetypes/Enum.h>",
					"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>",
					"#include <Refureku/TypeInfo/DefaultEntityRegisterer.h>",
					"#include <Refureku/Misc/DisableWarningMacros.h>",
					"\n");
}

void FileGenerationUnit::writeFooter(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerationUnit::writeFooter(file, parsingResult);

	file.writeLines("#ifdef " + _endFileMacroName,
					"	#undef " + _endFileMacroName,
					"#endif\n");

	generateEndFileMacro(file);
}

bool FileGenerationUnit::writeNamespaceToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& namespaceInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	if (kodgen::FileGenerationUnit::writeNamespaceToFile(generatedFile, namespaceInfo, genResult))
	{
		_generatedNamespaces.push_back(reinterpret_cast<kodgen::NamespaceInfo const*>(&namespaceInfo));

		return true;
	}

	return false;
}

bool FileGenerationUnit::writeStructOrClassToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& structClassInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	if (kodgen::FileGenerationUnit::writeStructOrClassToFile(generatedFile, structClassInfo, genResult))
	{
		_generatedClasses.push_back(reinterpret_cast<kodgen::StructClassInfo const*>(&structClassInfo));

		return true;
	}

	return false;
}

bool FileGenerationUnit::writeEnumToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& enumInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	if (kodgen::FileGenerationUnit::writeEnumToFile(generatedFile, enumInfo, genResult))
	{
		_generatedEnums.push_back(reinterpret_cast<kodgen::EnumInfo const*>(&enumInfo));

		return true;
	}

	return false;
}

bool FileGenerationUnit::writeVariableToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& variableInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	if (kodgen::FileGenerationUnit::writeVariableToFile(generatedFile, variableInfo, genResult))
	{
		_generatedVariables.push_back(reinterpret_cast<kodgen::VariableInfo const*>(&variableInfo));

		return true;
	}

	return false;
}

bool FileGenerationUnit::writeFunctionToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& functionInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	if (kodgen::FileGenerationUnit::writeFunctionToFile(generatedFile, functionInfo, genResult))
	{
		_generatedFunctions.push_back(reinterpret_cast<kodgen::FunctionInfo const*>(&functionInfo));

		return true;
	}

	return false;
}

void FileGenerationUnit::generateEndFileMacro(kodgen::GeneratedFile& file) const noexcept
{
	file.writeLines("#ifdef " + _endFileMacroName,
					"\t#undef " + _endFileMacroName,
					"#endif\n",
					"#define " + _endFileMacroName + "\t\\");

	//Enum first because structs/classes and namespaces can have nested (and then reference to) enums
	for (kodgen::EnumInfo const* enumInfo : _generatedEnums)
	{
		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(enumInfo->id)) + "u_GENERATED\t\\");
	}

	//Gen variables
	for (kodgen::VariableInfo const* varInfo : _generatedVariables)
	{
		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(varInfo->id)) + "u_GENERATED\t\\");
	}

	//Gen functions
	for (kodgen::FunctionInfo const* funcInfo : _generatedFunctions)
	{
		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(funcInfo->id)) + "u_GENERATED\t\\");
	}

	//Structs/Classes before namespaces because namespaces can have nested (and then reference to) structs/classes
	for (kodgen::StructClassInfo const* classInfo : _generatedClasses)
	{
		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(classInfo->id)) + "u_GetTypeDefinition\t\\");
	}

	for (kodgen::NamespaceInfo const* namespaceInfo : _generatedNamespaces)
	{
		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(namespaceInfo->id)) + "u_GENERATED\t\\");
	}

	//New line to avoid "warning: backslash-newline at end of file"
	file.writeLine("\n");
}