#pragma once

#include "Generated/ExampleClass2.rfk.h"

namespace namespace3 RFKNamespace()
{
	class RFKClass(ParseAllNested) AnotherClassInNamespace3
	{

		AnotherClassInNamespace3_GENERATED
	};

	RFKFunction()
	void functionInsideNamespace(int i) {}

	RFKVariable()
	int variableInsideNamespace;
}

RFKFunction() 
static void functionInsideGlobalScope(float j) {} 

RFKVariable()
static float variableInsideGlobalScope;

namespace test1::test2 RFKNamespace()
{
	enum class RFKEnum() NestedEnumInNestedNamespace : rfk::uint8
	{
		SomeValue = 42u
	};
}

File_GENERATED 