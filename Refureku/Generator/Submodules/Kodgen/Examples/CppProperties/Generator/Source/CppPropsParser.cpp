#include "CppPropsParser.h"

CppPropsParser::CppPropsParser() noexcept:
	FileParser()
{
	kodgen::ParsingSettings& parsingSettings = getParsingSettings();

	//We abort parsing if we encounter a single error while parsing
	parsingSettings.shouldAbortParsingOnFirstError = true;

	//Ignore and remove space character before collecting properties
	parsingSettings.propertyParsingSettings.ignoredCharacters = {' '};

	//Each property will be separed by a ,
	parsingSettings.propertyParsingSettings.propertySeparator = ',';

	//Subproperties are surrounded by []
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[0] = '[';
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[1] = ']';

	//Each subproperty will be separed by a ,
	parsingSettings.propertyParsingSettings.subPropertySeparator = ',';

	kodgen::PropertyRules& fieldPropertyRules = parsingSettings.propertyParsingSettings.fieldPropertyRules;

	//Define the Get property, which can take 
	fieldPropertyRules.addComplexPropertyRule("Get", "&|\\*|const|explicit");
	fieldPropertyRules.addComplexPropertyRule("Set", "explicit");

	//Define the macros to use for each entity type
	parsingSettings.propertyParsingSettings.classPropertyRules.macroName		= "KGClass";
	parsingSettings.propertyParsingSettings.structPropertyRules.macroName		= "KGStruct";
	fieldPropertyRules.macroName												= "KGField";
	parsingSettings.propertyParsingSettings.methodPropertyRules.macroName		= "KGMethod";
	parsingSettings.propertyParsingSettings.enumPropertyRules.macroName			= "KGEnum";
	parsingSettings.propertyParsingSettings.enumValuePropertyRules.macroName	= "KGEnumVal";
}

void CppPropsParser::preParse(fs::path const& parseFile) noexcept
{
	if (_logger != nullptr)
	{
		_logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void CppPropsParser::postParse(fs::path const&, kodgen::ParsingResult const& result) noexcept
{
	if (_logger != nullptr)
	{
		for (kodgen::ParsingError const& parsingError : result.parsingErrors)
		{
			_logger->log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		_logger->log("Found " + std::to_string(result.classes.size()) + " classes and " + std::to_string(result.enums.size()) + " enums.", kodgen::ILogger::ELogSeverity::Info);
	}
}