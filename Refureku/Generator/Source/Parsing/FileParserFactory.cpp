#include "RefurekuGenerator/Parsing/FileParserFactory.h"

using namespace rfk;

FileParserFactory::FileParserFactory() noexcept:
	kodgen::FileParserFactory<FileParser>()
{
	//We abort parsing if we encounter a single error during parsing
	parsingSettings.shouldAbortParsingOnFirstError = true;

	//Ignore and remove space character before collecting properties
	parsingSettings.propertyParsingSettings.ignoredCharacters = {' '};

	//Each property will be separated with a , (and potentially some spaces as they are ignored)
	parsingSettings.propertyParsingSettings.propertySeparator = ',';

	//Subproperties are surrounded by ()
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[0] = '(';
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[1] = ')';

	//Each subproperty will be separated with a , (and potentially some spaces as they are ignored)
	parsingSettings.propertyParsingSettings.subPropertySeparator = ',';

	//Define the Refureku property macros
	parsingSettings.propertyParsingSettings.namespaceMacroName	= "RFKNamespace";
	parsingSettings.propertyParsingSettings.classMacroName		= "RFKClass";
	parsingSettings.propertyParsingSettings.structMacroName		= "RFKStruct";
	parsingSettings.propertyParsingSettings.variableMacroName	= "RFKVariable";
	parsingSettings.propertyParsingSettings.fieldMacroName		= "RFKField";
	parsingSettings.propertyParsingSettings.functionMacroName	= "RFKFunction";
	parsingSettings.propertyParsingSettings.methodMacroName		= "RFKMethod";
	parsingSettings.propertyParsingSettings.enumMacroName		= "RFKEnum";
	parsingSettings.propertyParsingSettings.enumValueMacroName	= "RFKEnumVal";

	//Setup property rules
	parsingSettings.propertyParsingSettings.simplePropertyRules.emplace_back(&_customInstantiatorPropertyRule);
}