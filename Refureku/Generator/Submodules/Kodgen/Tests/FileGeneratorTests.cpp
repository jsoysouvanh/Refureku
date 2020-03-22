#include <iostream>
#include <cassert>

#include "Parsing/FileParser.h"
#include "CodeGen/FileGenerator.h"

#include "TestGeneratedCodeTemplate.h"

static std::string const TestFile =
"#pragma once																																				\n"

"//#include \"Generated/TestClass.kodgen.h\"																												\n"
"																																							\n"
"#include <filesystem>																																		\n"
"#include <vector>																																			\n"
"#include <string>																																			\n"
"																																							\n"
"namespace TestNamespace																																	\n"
"{																																							\n"
"	class Class1{};																																			\n"
"	class Class2{};																																			\n"
"	class Class3{};																																			\n"
"	using Class1Typename = Class1;																															\n"
"	using Class1PtrTypename = Class1*;																														\n"
"																																							\n"
"	class Class(GenTemplate[TestTemplate], ClassProp1, ClassProp2[ClassSubProp21, ClassSubProp22], ClassProp3) TestClass final : public Class1Typename, protected Class2, private Class3			\n"
"	{																																						\n"
"		private:																																			\n"
"		#pragma region Variables																															\n"
"																																							\n"
"		Field(FieldProp1, FieldProp2[FieldSubProp21, FieldSubProp22], FieldProp3)																			\n"
"		const volatile int* const&	var1;																													\n"
"																																							\n"
"		#pragma endregion																																	\n"
"																																							\n"
"		protected:																																			\n"
"		Field(FieldProp2[])																																\n"
"		Class1PtrTypename*		var4 = nullptr;																												\n"
"																																							\n"
"		public:																																				\n"
"		Field(FieldProp1)																																	\n"
"		static int var2 : 1;																																\n"
"																																							\n"
"		Field(FieldProp1)																																	\n"
"		unsigned long long	_someUnsignedLongLong;																											\n"
"																																							\n"
"		#pragma region Methods																																\n"
"																																							\n"
"		Method(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)																	\n"
"		virtual const volatile int* const& someMethod(int someMethodParam1, Class1Typename&) const final;													\n"
"																																							\n"
"		Method(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)																	\n"
"		virtual int someMethod2(int param1, class Hey* param2) final																						\n"
"		{																																					\n"
"																																							\n"
"		}																																					\n"
"																																							\n"
"		int dsomeMethod3(int) noexcept;																														\n"
"		//int someMethosd3(int) override;																													\n"
"		virtual int someMethodd3(int) const;																												\n"
"																																							\n"
"		#pragma endregion																																	\n"
"																																							\n"
"		Field()																																			\n"
"		float const		var3;																																\n"
"	};																																						\n"
"																																							\n"
"	enum class Enum(GenTemplate[TestTemplate], EnumProp1, EnumProp2[EnumSubProp21, EnumSubProp22], EnumProp3) MyEnum : uint8_t							\n"
"	{																																						\n"
"		EVal1 EnumVal(EnumValueProp1, EnumValueProp2[EnumValueSubProp21, EnumValueSubProp22], EnumValueProp3) = 1 << 0,									\n"
"		EVal2 = 1 << 1,																																		\n"
"		a,																																					\n"
"		b,																																					\n"
"		Count = 42,																																			\n"
"		c																																					\n"
"	};																																						\n"
"																																							\n"
"	class Class() TestClass2																																\n"
"	{																																						\n"
"		private:																																			\n"
"		#pragma region Variables																															\n"
"																																							\n"
"		Field()																																			\n"
"		int				var1 = 42;																															\n"
"		float			var2;																																\n"
"																																							\n"
"		#pragma endregion																																	\n"
"																																							\n"
"		protected:																																			\n"
"																																							\n"
"		public:																																				\n"
"		#pragma region Methods																																\n"
"																																							\n"
"		Method()																																			\n"
"		static int someMethod(int);																															\n"
"		int dsomeMethod3(int) noexcept;																														\n"
"		virtual int someMethodd3(int) const;																												\n"
"																																							\n"
"		#pragma endregion																																	\n"
"	};																																						\n"
"}																																							\n";

static std::string const TestFile2 =
"#pragma once																																				\n"
"//#include \"Generated/TestClass.kodgen.h\"																												\n"
"																																							\n"
"#include <filesystem>																																		\n"
"#include <vector>																																			\n"
"#include <string>																																			\n"
"																																							\n"
"namespace TestNamespace																																	\n"
"{																																							\n"
"	class Class1{};																																			\n"
"	using Class1Typename = Class1*;																															\n"
"																																							\n"
"	class Class(GenTemplate[TestTemplate], ClassProp1, ClassProp2[ClassSubProp21, ClassSubProp22], ClassProp3) TestClassBis final : public Class1			\n"
"	{																																						\n"
"		private:																																			\n"
"		#pragma region Variables																															\n"
"																																							\n"
"		Field(FieldProp1, FieldProp2[FieldSubProp21, FieldSubProp22], FieldProp3)																			\n"
"		const volatile int* const&	var1;																													\n"
"																																							\n"
"		#pragma endregion																																	\n"
"																																							\n"
"		protected:																																			\n"
"		Field(FieldProp2[])																																\n"
"		Class1Typename*		var4 = nullptr;																													\n"
"																																							\n"
"		public:																																				\n"
"		Field(FieldProp1)																																	\n"
"		static int var2 : 1;																																\n"
"																																							\n"
"		Field(FieldProp1)																																	\n"
"		unsigned long long	_someUnsignedLongLong;																											\n"
"																																							\n"
"		#pragma region Methods																																\n"
"																																							\n"
"		Method(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)																	\n"
"		virtual const volatile int* const& someMethod(int param1, Class1Typename& param2) const final;														\n"
"																																							\n"
"		Method(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)																	\n"
"		virtual int someMethod2(int param1, class Hey* param2) final																						\n"
"		{																																					\n"
"																																							\n"
"		}																																					\n"
"																																							\n"
"		int dsomeMethod3(int) noexcept;																														\n"
"		//int someMethosd3(int) override;																													\n"
"		virtual int someMethodd3(int) const;																												\n"
"																																							\n"
"		#pragma endregion																																	\n"
"																																							\n"
"		Field()																																			\n"
"		float const		var3;																																\n"
"	};																																						\n"
"																																							\n"
"	enum class Enum(GenTemplate[TestTemplate], EnumProp1, EnumProp2[EnumSubProp21, EnumSubProp22], EnumProp3) MyEnumBis : uint8_t							\n"
"	{																																						\n"
"		EVal1 EnumVal(EnumValueProp1, EnumValueProp2[EnumValueSubProp21, EnumValueSubProp22], EnumValueProp3) = 1 << 0,									\n"
"			EVal2 = 1 << 1,																																	\n"
"			a,																																				\n"
"			b,																																				\n"
"			Count = 42,																																		\n"
"			c																																				\n"
"	};																																						\n"
"																																							\n"
"	class Class() TestClassBis2																															\n"
"	{																																						\n"
"		private:																																			\n"
"		#pragma region Variables																															\n"
"																																							\n"
"		Field()																																			\n"
"		int				var1 = 42;																															\n"
"		float			var2;																																\n"
"																																							\n"
"		#pragma endregion																																	\n"
"																																							\n"
"		protected:																																			\n"
"																																							\n"
"		public:																																				\n"
"		#pragma region Methods																																\n"
"																																							\n"
"		Method()																																			\n"
"		static int someMethod(int);																															\n"
"		int dsomeMethod3(int) noexcept;																														\n"
"		virtual int someMethodd3(int) const;																												\n"
"																																							\n"
"		#pragma endregion																																	\n"
"	};																																						\n"
"}																																							\n";

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

int main()
{
	//Create the files we are going to read
	std::ofstream testFileStream((fs::current_path() / "TestClass.h").string(), std::ios::out | std::ios::trunc);
	testFileStream << TestFile;
	testFileStream.close();

	std::ofstream testFileStream2((fs::current_path() / "TestClassBis.h").string(), std::ios::out | std::ios::trunc);
	testFileStream2 << TestFile2;
	testFileStream2.close();

	//Setup parser
	kodgen::FileParser parser;

	setupParser(parser);

	//Setup FileGenerator
	kodgen::FileGenerator fg;

	fs::path includeDirPath	= fs::current_path();
	fs::path pathToFile		= includeDirPath / "TestClass.h";

	fg.outputDirectory = includeDirPath / "Generated";

	fg.addGeneratedCodeTemplate("TestTemplate", new kodgen::TestGeneratedCodeTemplate());
	fg.setDefaultClassTemplate("TestTemplate");

	//Add files/directories to parse
	fg.includedFiles.emplace(pathToFile.string());

	kodgen::FileGenerationResult fgr = fg.generateFiles(parser, true);

	std::cout << "File generation: " << ((fgr.completed) ? "Success" : "Failure") << std::endl;

	for (kodgen::ParsingError& pe : fgr.parsingErrors)
	{
		std::cout << pe << std::endl;
	}

	for (kodgen::FileGenerationError& fge : fgr.fileGenerationErrors)
	{
		std::cout << fge << std::endl;
	}

	return EXIT_SUCCESS;
}