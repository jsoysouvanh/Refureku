#pragma once

#include "Test.h"

#include "Generated/TestPropertyUsage.rfk.h"

namespace testPropertyUsageNamespace RFKNamespace(TestProperty())
{

}

//struct RFKStruct(TestProperty()) TestPropertyUsageStruct
//{
//	TestPropertyUsageStruct_GENERATED
//};

class RFKClass(TestProperty()) TestPropertyUsageClass
{
	RFKField(TestProperty())
	int i;

	RFKMethod(TestProperty())
	void method(){}

	TestPropertyUsageClass_GENERATED
};

enum class RFKEnum(TestProperty())
	TestPropertyUsageEnum
{
	EnumValue1 RFKEnumVal(TestProperty()) = 0,
	EnumValue2 RFKEnumVal(TestProperty()) = 1
};

RFKFunction(TestProperty())
inline void function(){}

RFKVariable(TestProperty())
inline int var = 0;

File_GENERATED