#include "FileParser.h"

using namespace rfk;

FileParser::FileParser() noexcept:
	kodgen::FileParser()
{
	kodgen::ParsingSettings& parsingSettings = getParsingSettings();

	//We abort parsing if we encounter a single error during parsing
	parsingSettings.shouldAbortParsingOnFirstError = true;

	kodgen::PropertyParsingSettings& pps = parsingSettings.propertyParsingSettings;

	//Ignore and remove space character before collecting properties
	pps.ignoredCharacters = {' '};

	//Each property will be separated with a , (and potentially some spaces as they are ignored)
	pps.propertySeparator = ',';

	//Subproperties are surrounded by []
	pps.subPropertyEnclosers[0] = '[';
	pps.subPropertyEnclosers[1] = ']';

	//Each subproperty will be separated with a , (and potentially some spaces as they are ignored)
	pps.subPropertySeparator = ',';

	//Define the Refureku property macros
	pps.classPropertyRules.macroName		= "RFKClass";
	pps.structPropertyRules.macroName		= "RFKStruct";
	pps.fieldPropertyRules.macroName		= "RFKField";
	pps.methodPropertyRules.macroName		= "RFKMethod";
	pps.enumPropertyRules.macroName			= "RFKEnum";
	pps.enumValuePropertyRules.macroName	= "RFKEnumVal";
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