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
}

void FileGenerator::writeNamespaceToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& namespaceInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	kodgen::FileGenerator::writeNamespaceToFile(generatedFile, namespaceInfo, genResult);
}

void FileGenerator::writeStructOrClassToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& structClassInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	kodgen::FileGenerator::writeStructOrClassToFile(generatedFile, structClassInfo, genResult);
}

void FileGenerator::writeEnumToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& enumInfo, kodgen::FileGenerationResult& genResult) noexcept
{
	kodgen::FileGenerator::writeEnumToFile(generatedFile, enumInfo, genResult);
}