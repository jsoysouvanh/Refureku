#include "CppPropsParserFactory.h"

CppPropsParserFactory::CppPropsParserFactory() noexcept:
	kodgen::FileParserFactory<CppPropsParser>()
{
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

	//kodgen::PropertyRules& fieldPropertyRules = parsingSettings.propertyParsingSettings.fieldPropertyRules;

	////Define the Get property, which can take
	parsingSettings.propertyParsingSettings.complexPropertyRules.push_back(&_getPropertyRule);
	parsingSettings.propertyParsingSettings.complexPropertyRules.push_back(&_setPropertyRule);

	//Define the macros to use for each entity type
	parsingSettings.propertyParsingSettings.namespaceMacroName	= "KGNamespace";
	parsingSettings.propertyParsingSettings.classMacroName		= "KGClass";
	parsingSettings.propertyParsingSettings.structMacroName		= "KGStruct";
	parsingSettings.propertyParsingSettings.fieldMacroName		= "KGVariable";
	parsingSettings.propertyParsingSettings.fieldMacroName		= "KGField";
	parsingSettings.propertyParsingSettings.functionMacroName	= "KGFunction";
	parsingSettings.propertyParsingSettings.methodMacroName		= "KGMethod";
	parsingSettings.propertyParsingSettings.enumMacroName		= "KGEnum";
	parsingSettings.propertyParsingSettings.enumValueMacroName	= "KGEnumVal";
}