#include "FileParser.h"

using namespace refureku;

FileParser::FileParser() noexcept:
	kodgen::FileParser()
{
	kodgen::ParsingSettings& parsingSettings = getParsingSettings();

	//We abort parsing if we encounter a single error during parsing
	parsingSettings.shouldAbortParsingOnFirstError = true;

	//Ignore and remove space character before collecting properties
	parsingSettings.propertyParsingSettings.ignoredCharacters = {' '};

	//Each property will be separated with a , (and potentially some spaces as they are ignored)
	parsingSettings.propertyParsingSettings.propertySeparator = ',';

	//Subproperties are surrounded by []
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[0] = '[';
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[1] = ']';

	//Each subproperty will be separated with a , (and potentially some spaces as they are ignored)
	parsingSettings.propertyParsingSettings.subPropertySeparator = ',';

	//Define the Refureku specific properties
	//None.
}

void FileParser::preParse(fs::path const& parseFile) noexcept
{
	std::cout << "Start parsing: " << parseFile.string() << std::endl;
}

void FileParser::postParse(fs::path const&, kodgen::ParsingResult const& result) noexcept
{
	for (kodgen::ParsingError const& parsingError : result.parsingErrors)
	{
		std::cout << parsingError << std::endl;
	}

	std::cout << "Found " << result.classes.size() << " classes and " << result.enums.size() << " enums." << std::endl;
}