#include "FileParser.h"

#include "Keywords.h"

using namespace rfk;

FileParser::FileParser() noexcept:
	kodgen::FileParser()
{
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

	//Define the Refureku property macros
	parsingSettings.propertyParsingSettings.namespacePropertyRules.macroName	= "RFKNamespace";
	parsingSettings.propertyParsingSettings.classPropertyRules.macroName		= "RFKClass";
	parsingSettings.propertyParsingSettings.structPropertyRules.macroName		= "RFKStruct";
	parsingSettings.propertyParsingSettings.fieldPropertyRules.macroName		= "RFKField";
	parsingSettings.propertyParsingSettings.methodPropertyRules.macroName		= "RFKMethod";
	parsingSettings.propertyParsingSettings.enumPropertyRules.macroName			= "RFKEnum";
	parsingSettings.propertyParsingSettings.enumValuePropertyRules.macroName	= "RFKEnumVal";

	parsingSettings.propertyParsingSettings.classPropertyRules.addSimplePropertyRule(__RFK_CLASS_DYNAMIC_GET_ARCHETYPE);
	parsingSettings.propertyParsingSettings.structPropertyRules.addSimplePropertyRule(__RFK_CLASS_DYNAMIC_GET_ARCHETYPE);
	parsingSettings.propertyParsingSettings.methodPropertyRules.addSimplePropertyRule(__RFK_CLASS_CUSTOM_INSTANTIATOR);
}

void FileParser::preParse(fs::path const& parseFile) noexcept
{
	if (logger != nullptr)
	{
		logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void FileParser::postParse(fs::path const&, kodgen::FileParsingResult const& result) noexcept
{
	if (logger != nullptr)
	{
		for (kodgen::ParsingError const& parsingError : result.errors)
		{
			logger->log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		logger->log("Found " + std::to_string(result.namespaces.size()) + " namespaces, " +
					std::to_string(result.structs.size()) + " structs, " +
					std::to_string(result.classes.size()) + " classes and " +
					std::to_string(result.enums.size()) + " enums.", kodgen::ILogger::ELogSeverity::Info);
	}
}