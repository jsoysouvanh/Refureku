#include "FileGenerator.h"

using namespace rfk;

void FileGenerator::writeHeader(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerator::writeHeader(file, parsingResult);

	file.writeLine("#include \"TypeInfo/Archetypes/Class.h\"");
	file.writeLine("#include \"TypeInfo/Registration/ArchetypeRegisterer.h\"\n");
}

void FileGenerator::writeFooter(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept
{
	//Always call base class
	kodgen::FileGenerator::writeFooter(file, parsingResult);
}