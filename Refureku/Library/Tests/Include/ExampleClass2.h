#pragma once

#include <Refureku/NativeProperties.h>

#include "ExampleClass.h"

#include "Generated/ExampleClass2.rfk.h"

namespace namespace3 RFKNamespace(ParseAllNested)
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

RFKFunction()
void function1(namespace3::ExampleClass) { }

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

RFKFunction()
inline int inlineFunction(int i) { return i; }

namespace ExampleNamespace RFKNamespace()
{
	RFKFunction()
	void functionInsideNamespace() { }
}

File_GENERATED