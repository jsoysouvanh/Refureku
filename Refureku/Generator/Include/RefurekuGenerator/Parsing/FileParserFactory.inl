/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename FileParserType>
FileParserFactory<FileParserType>::FileParserFactory() noexcept:
	kodgen::FileParserFactory<FileParserType>()
{
	//We abort parsing if we encounter a single error during parsing
	this->parsingSettings.shouldAbortParsingOnFirstError = true;

	//Each property will be separated with a ,
	this->parsingSettings.propertyParsingSettings.propertySeparator = ',';

	//Subproperties are surrounded by ()
	this->parsingSettings.propertyParsingSettings.subPropertyEnclosers[0] = '(';
	this->parsingSettings.propertyParsingSettings.subPropertyEnclosers[1] = ')';

	//Each subproperty will be separated with a ,
	this->parsingSettings.propertyParsingSettings.subPropertySeparator = ',';

	//Define the Refureku property macros
	this->parsingSettings.propertyParsingSettings.namespaceMacroName	= "RFKNamespace";
	this->parsingSettings.propertyParsingSettings.classMacroName		= "RFKClass";
	this->parsingSettings.propertyParsingSettings.structMacroName		= "RFKStruct";
	this->parsingSettings.propertyParsingSettings.variableMacroName		= "RFKVariable";
	this->parsingSettings.propertyParsingSettings.fieldMacroName		= "RFKField";
	this->parsingSettings.propertyParsingSettings.functionMacroName		= "RFKFunction";
	this->parsingSettings.propertyParsingSettings.methodMacroName		= "RFKMethod";
	this->parsingSettings.propertyParsingSettings.enumMacroName			= "RFKEnum";
	this->parsingSettings.propertyParsingSettings.enumValueMacroName	= "RFKEnumVal";

	//Setup property rules
	this->parsingSettings.propertyParsingSettings.simplePropertyRules.emplace_back(&_customInstantiatorPropertyRule);
	this->parsingSettings.propertyParsingSettings.complexPropertyRules.emplace_back(&_propertySettingsPropertyRule);
	this->parsingSettings.propertyParsingSettings.complexPropertyRules.emplace_back(&_testPropertyRule);
}