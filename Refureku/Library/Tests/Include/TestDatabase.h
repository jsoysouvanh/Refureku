/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestProperties.h"

#include "Generated/TestDatabase.rfkh.h"

class CLASS(PropertySettings(allEntityKinds)) TestDabataseProperty : public rfk::Property
{
	TestDabataseProperty_GENERATED
};

VARIABLE(TestDabataseProperty)
inline int			fileLevelVar	= 2;

VARIABLE()
inline int const	fileLevelVar2	= 2;

VARIABLE(TestDabataseProperty)
inline int			fileLevelVar3	= 2;

FUNCTION(TestDabataseProperty)
inline void fileLevelFunc() {}

FUNCTION()
inline void fileLevelFunc2() {}

FUNCTION(TestDabataseProperty)
inline void fileLevelFunc3() {}

class CLASS(TestDabataseProperty) FileLevelClass
{
	private:
		FIELD()
		int _field;

		FIELD()
		inline static int _staticField = 42;

		METHOD()
		void method() {}

		METHOD()
		static void staticMethod() {}

	public:
		class CLASS() ClassClass
		{
			FileLevelClass_ClassClass_GENERATED
		};

		struct STRUCT() ClassStruct
		{
			FileLevelClass_ClassStruct_GENERATED
		};

		enum ENUM() ClassEnum
		{
			Value1 ENUMVALUE() = 0
		};

	FileLevelClass_GENERATED
};

class CLASS() FileLevelClass2
{
	FileLevelClass2_GENERATED
};

class CLASS(TestDabataseProperty) FileLevelClass3
{
	FileLevelClass3_GENERATED
};

struct STRUCT(TestDabataseProperty) FileLevelStruct
{
	FileLevelStruct_GENERATED
};

struct STRUCT() FileLevelStruct2
{
	FileLevelStruct2_GENERATED
};

struct STRUCT(TestDabataseProperty) FileLevelStruct3
{
	FileLevelStruct3_GENERATED
};

enum class ENUM(TestDabataseProperty) FileLevelEnum
{
	Value1 ENUMVALUE() = 0,
	Value2
};

enum class ENUM() FileLevelEnum2
{
	Value1 ENUMVALUE() = 0,
	Value2
};

enum class ENUM(TestDabataseProperty) FileLevelEnum3
{
	Value1 ENUMVALUE() = 0,
	Value2
};

namespace filelevel_namespace NAMESPACE(TestDabataseProperty)
{
	VARIABLE()
	inline int namespaceVar = 2;

	FUNCTION()
	inline void namespaceFunc() {}

	namespace nested_namespace NAMESPACE()
	{
	}

	class CLASS() NamespaceClass
	{
		filelevel_namespace_NamespaceClass_GENERATED
	};

	struct STRUCT() NamespaceStruct
	{
		filelevel_namespace_NamespaceStruct_GENERATED
	};

	enum ENUM() NamespaceEnum
	{
		Value1 ENUMVALUE() = 0
	};
}

namespace filelevel_namespace2 NAMESPACE()
{

}

namespace filelevel_namespace3 NAMESPACE(TestDabataseProperty)
{

}

File_TestDatabase_GENERATED