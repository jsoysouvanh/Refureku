#include <iostream>
#include <cassert>

#include "Parsing/FileParser.h"

void setupParser(kodgen::FileParser& parser)
{
	kodgen::ParsingSettings& parsingSettings = parser.getParsingSettings();

	//Setup parser settings
	parsingSettings.shouldAbortParsingOnFirstError = false;

	parsingSettings.propertyParsingSettings.ignoredCharacters.insert(' ');	//Ignore white space
	parsingSettings.propertyParsingSettings.subPropertySeparator = ',';

	//ClassProp1, ClassProp2[ClassSubProp21, ClassSubProp22], ClassProp3
	kodgen::PropertyRules& classPropertyRules = parsingSettings.propertyParsingSettings.classPropertyRules;

	classPropertyRules.addSimplePropertyRule("ClassProp1");
	classPropertyRules.addSimplePropertyRule("ClassProp2");
	classPropertyRules.addComplexPropertyRule("ClassProp2", "ClassSubProp2[1-9]");
	classPropertyRules.addSimplePropertyRule("ClassProp3");

	//MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3
	kodgen::PropertyRules& methodPropertyRules = parsingSettings.propertyParsingSettings.methodPropertyRules;

	methodPropertyRules.addSimplePropertyRule("MethodProp1");
	methodPropertyRules.addSimplePropertyRule("MethodProp2");
	methodPropertyRules.addComplexPropertyRule("MethodProp2", "MethodSubProp2[1-9]");
	methodPropertyRules.addSimplePropertyRule("MethodProp3");

	//FieldProp1, FieldProp2[FieldSubProp21, FieldSubProp22], FieldProp3
	kodgen::PropertyRules& fieldPropertyRules = parsingSettings.propertyParsingSettings.fieldPropertyRules;

	fieldPropertyRules.addSimplePropertyRule("FieldProp1");
	fieldPropertyRules.addSimplePropertyRule("FieldProp2");
	fieldPropertyRules.addComplexPropertyRule("FieldProp2", "FieldSubProp2[1-9]");
	fieldPropertyRules.addSimplePropertyRule("FieldProp3");

	//EnumProp1, EnumProp2[EnumSubProp21, EnumSubProp22], EnumProp3
	kodgen::PropertyRules& enumPropertyRules = parsingSettings.propertyParsingSettings.enumPropertyRules;

	enumPropertyRules.addSimplePropertyRule("EnumProp1");
	enumPropertyRules.addSimplePropertyRule("EnumProp2");
	enumPropertyRules.addComplexPropertyRule("EnumProp2", "EnumSubProp2[1-9]");
	enumPropertyRules.addSimplePropertyRule("EnumProp3");

	//EnumValueProp1, EnumValueProp2[EnumValueSubProp21, EnumValueSubProp22], EnumValueProp3
	kodgen::PropertyRules& enumValuePropertyRules = parsingSettings.propertyParsingSettings.enumValuePropertyRules;

	enumValuePropertyRules.addSimplePropertyRule("EnumValueProp1");
	enumValuePropertyRules.addSimplePropertyRule("EnumValueProp2");
	enumValuePropertyRules.addComplexPropertyRule("EnumValueProp2", "EnumValueSubProp2[1-9]");
	enumValuePropertyRules.addSimplePropertyRule("EnumValueProp3");
}
//
//void parsingTests()
//{
//	fs::path includeDirPath	= fs::current_path().parent_path().parent_path().parent_path() / "Include";
//	fs::path pathToFile		= includeDirPath / "TestClass.h";
//
//	kodgen::Parser parser;
//
//	setupParser(parser);
//
//	//Check result
//	kodgen::ParsingResult parsingResult;
//	bool success = parser.parse(pathToFile, parsingResult);
//
//	if (success)
//	{
//		std::cout << "Parse success" << std::endl;
//
//		printClasses(parsingResult);
//	}
//	else
//	{
//		std::cout << "Parse ended with errors" << std::endl;
//
//		printErrors(parsingResult);
//	}
//}

int main()
{
	return EXIT_SUCCESS;
}