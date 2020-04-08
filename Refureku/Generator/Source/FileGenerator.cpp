#include "FileGenerator.h"

using namespace rfk;

FileGenerator::FileGenerator() noexcept:
	kodgen::FileGenerator()
{
	//Generated files will use .rfk.h extension
	generatedFilesExtension = ".rfk.h";

	//Only parse .h files
	supportedExtensions.emplace(".h");
	supportedExtensions.emplace(".hpp");
}

void FileGenerator::writeHeader(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerator::writeHeader(file, parsingResult);

	file.writeLine("#include \"Utility/TypeTraits.h\"");
	file.writeLine("#include \"TypeInfo/Archetypes/Class.h\"");
	file.writeLine("#include \"TypeInfo/Archetypes/Enum.h\"");
	file.writeLine("#include \"TypeInfo/Archetypes/ArchetypeRegisterer.h\"\n");
}

void FileGenerator::writeFooter(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerator::writeFooter(file, parsingResult);
}