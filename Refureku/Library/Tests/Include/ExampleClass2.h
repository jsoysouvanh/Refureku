#pragma once

#include "ExampleClass.h"

#include "Generated/ExampleClass2.rfk.h"

namespace namespace3 RFKNamespace()
{
	class RFKClass(ParseAllNested) AnotherClassInNamespace3
	{

		AnotherClassInNamespace3_GENERATED
	};

	RFKFunction()
	inline void functionInsideNamespace(int i) { i; } 

	RFKFunction()
	int function1(int i) { return i; }

	RFKFunction()
	int function1(int i, int j) { return i + j; }

	RFKVariable()
	int variableInsideNamespace = 42;
}

RFKFunction() 
static void functionInsideGlobalScope(float j) { j; } 

RFKFunction()
int function1(int i) { return i; }

RFKFunction()
int function1(int i, int j) { return i + j; }

RFKVariable()
static float variableInsideGlobalScope = 10.0f;

namespace test1::test2 RFKNamespace()
{
	enum class RFKEnum() NestedEnumInNestedNamespace : rfk::uint8
	{
		SomeValue = 42u
	};
}

enum RFKEnum() EThisIsANormalEnum : int
{
	Value1 = 0,
	Value2
};

File_GENERATED