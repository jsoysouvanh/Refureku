#pragma once

#include "Refureku/Properties/ParseAllNested.h"

#include "Generated/ReworkTest.rfkh.h"

RFKVariable()
extern int reworkVariable;

RFKFunction()
extern void reworkFunction(int i, float j) noexcept;

enum class RFKEnum() EReworkEnum
{
	Value1 RFKEnumVal() = 0,
	Value2 RFKEnumVal(),
	Value3
};

class RFKClass(ParseAllNested) ReworkClass
{
	RFKField()
	int reworkField = 0;

	RFKMethod()
	void reworkMethod(int, float) const;

	RFKMethod()
	void reworkMethod(int, float);

	ReworkClass_GENERATED
};


struct RFKStruct() ReworkStruct : public ReworkClass
{
	RFKField()
	static int reworkStaticField;

	RFKMethod()
	static float reworkStaticMethod() noexcept;

	ReworkStruct_GENERATED
};

class NonReflectedClass {};

class RFKClass() ReworkClass2 : public NonReflectedClass
{
	//Nested class
	class RFKClass() ReworkClass2NestedClass
	{
		ReworkClass2_ReworkClass2NestedClass_GENERATED
	};

	//Nested struct
	struct RFKStruct() ReworkClass2NestedStruct
	{
		ReworkClass2_ReworkClass2NestedStruct_GENERATED
	};

	//Nested enum
	enum class RFKEnum() ReworkClass2NestedEnum
	{

	};

	ReworkClass2_GENERATED
};

namespace rework_namespace RFKNamespace(ParseAllNested)
{
	RFKVariable()
	extern int reworkNamespaceVariable;

	RFKFunction()
	extern void reworkNamespaceFunction(int i, float j) noexcept;

	enum class RFKEnum() EReworkEnum
	{
		Value1 RFKEnumVal() = 0,
		Value2 RFKEnumVal(),
		Value3
	};

	class RFKClass(ParseAllNested) ReworkClass
	{
		rework_namespace_ReworkClass_GENERATED
	};


	struct RFKStruct() ReworkStruct : public ReworkClass
	{
		rework_namespace_ReworkStruct_GENERATED
	};
}

File_ReworkTest_GENERATED