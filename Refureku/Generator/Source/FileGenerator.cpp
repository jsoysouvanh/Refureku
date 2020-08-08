#include "RefurekuGenerator/FileGenerator.h"

using namespace rfk;

std::string const				FileGenerator::_endFileMacroName = "File_GENERATED";
std::hash<std::string> const	FileGenerator::_stringHasher;

FileGenerator::FileGenerator() noexcept:
	kodgen::FileGenerator()
{
	//Generated files will use .rfk.h extension
	generatedFilesExtension = ".rfk.h";

	//Only parse .h and .hpp files
	supportedExtensions.emplace(".h");
	supportedExtensions.emplace(".hpp");

	//Bind name -> templates
	addGeneratedCodeTemplate("RefurekuNamespace", &_namespaceCodeTemplate);
	addGeneratedCodeTemplate("RefurekuClass", &_classCodeTemplate);
	addGeneratedCodeTemplate("RefurekuEnum", &_enumCodeTemplate);

	/**
	*	namespace MyNamespace RFKNamespace() {}
	*	class RFKClass() MyClass {};
	*	enum [class] RFKEnum() MyEnum {};
	*/
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Namespace, "RefurekuNamespace");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Class, "RefurekuClass");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Struct, "RefurekuClass");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Enum, "RefurekuEnum");
}

void FileGenerator::postGenerateFile() noexcept
{
	_generatedNamespaces.clear();
	_generatedClasses.clear();
	_generatedEnums.clear();
}

void FileGenerator::writeHeader(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerator::writeHeader(file, parsingResult);

	file.writeLines("#include <Refureku/TypeInfo/Namespaces/Namespace.h>",
					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>",
					"#include <Refureku/TypeInfo/Archetypes/Class.h>",
					"#include <Refureku/TypeInfo/Archetypes/Enum.h>",
					"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>",
					"#include <Refureku/Misc/DisableWarningMacros.h>",
					"\n");
}

void FileGenerator::writeFooter(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerator::writeFooter(file, parsingResult);

	file.writeLines("#ifdef " + _endFileMacroName,
					"	#undef " + _endFileMacroName,
					"#endif\n");

	generateEndFileMacro(file);
}

void FileGenerator::writeNamespaceToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& namespaceInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	kodgen::FileGenerator::writeNamespaceToFile(generatedFile, namespaceInfo, genResult);

	_generatedNamespaces.push_back(reinterpret_cast<kodgen::NamespaceInfo const*>(&namespaceInfo));
}

void FileGenerator::writeStructOrClassToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& structClassInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	kodgen::FileGenerator::writeStructOrClassToFile(generatedFile, structClassInfo, genResult);

	_generatedClasses.push_back(reinterpret_cast<kodgen::StructClassInfo const*>(&structClassInfo));
}

void FileGenerator::writeEnumToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& enumInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	kodgen::FileGenerator::writeEnumToFile(generatedFile, enumInfo, genResult);

	_generatedEnums.push_back(reinterpret_cast<kodgen::EnumInfo const*>(&enumInfo));
}

void FileGenerator::generateEndFileMacro(kodgen::GeneratedFile& file) const noexcept
{
	file.writeLine("#define " + _endFileMacroName + "\t\\");

	//Enum first because structs/classes and namespaces can have nested (and then reference to) enums
	for (kodgen::EnumInfo const* enumInfo : _generatedEnums)
	{
		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(enumInfo->id)) + "u_GENERATED\t\\");
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
}