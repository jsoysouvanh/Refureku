#include "FileGenerator.h"

#include "GeneratedClassCodeTemplate.h"
#include "GeneratedEnumCodeTemplate.h"

using namespace rfk;

FileGenerator::FileGenerator() noexcept:
	kodgen::FileGenerator()
{
	//Generated files will use .rfk.h extension
	generatedFilesExtension = ".rfk.h";

	//Only parse .h files
	supportedExtensions.emplace(".h");
	supportedExtensions.emplace(".hpp");

	//Bind name -> templates
	addGeneratedCodeTemplate("RefurekuClass", new rfk::GeneratedClassCodeTemplate());
	addGeneratedCodeTemplate("RefurekuEnum", new rfk::GeneratedEnumCodeTemplate());

	/**	class RFKClass() MyClass {}; enum [class] RFKEnum() {}; */
	setDefaultGeneratedCodeTemplate(kodgen::EntityInfo::EType::Class, "RefurekuClass");
	setDefaultGeneratedCodeTemplate(kodgen::EntityInfo::EType::Struct, "RefurekuClass");
	setDefaultGeneratedCodeTemplate(kodgen::EntityInfo::EType::Enum, "RefurekuEnum");
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

	file.writeLines("#include \"TypeInfo/Archetypes/Class.h\"",
					"#include \"TypeInfo/Archetypes/Enum.h\"",
					"#include \"TypeInfo/Archetypes/ArchetypeRegisterer.h\"",
					"#include \"Misc/DisableWarningMacros.h\"",
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

	for (kodgen::EnumInfo const* enumInfo : _generatedEnums)
	{
		file.writeLine("	" + std::string(_internalPrefix) + enumInfo->name + "_GENERATED\t\\");
	}

	for (kodgen::StructClassInfo const* classInfo : _generatedClasses)
	{
		file.writeLine("	" + std::string(_internalPrefix) + classInfo->name + "_GetTypeDefinition\t\\");
	}
}