#include "FileParser.h"

#include "Keywords.h"

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

	pps.classPropertyRules.addSimplePropertyRule(__RFK_CLASS_DYNAMIC_GET_ARCHETYPE);
	pps.structPropertyRules.addSimplePropertyRule(__RFK_CLASS_DYNAMIC_GET_ARCHETYPE);
	pps.methodPropertyRules.addSimplePropertyRule(__RFK_CLASS_CUSTOM_INSTANTIATOR);
}

void FileParser::preParse(fs::path const& parseFile) noexcept
{
	if (_logger != nullptr)
	{
		_logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void FileParser::postParse(fs::path const&, kodgen::ParsingResult const& result) noexcept
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