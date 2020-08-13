#pragma once

#include "Generated/ExampleClass2.rfk.h"

namespace namespace3 RFKNamespace()
{
	class RFKClass(ParseAllNested) AnotherClassInNamespace3
	{

		AnotherClassInNamespace3_GENERATED
	};

	RFKFunction()
	inline void functionInsideNamespace(int i) {} 

	RFKVariable()
	int variableInsideNamespace = 42;
}

RFKFunction() 
static void functionInsideGlobalScope(float j) {} 

RFKVariable()
static float variableInsideGlobalScope = 10.0f;

namespace test1::test2 RFKNamespace()
{
	enum class RFKEnum() NestedEnumInNestedNamespace : rfk::uint8
	{
		SomeValue = 42u
	};
}

File_GENERATED 