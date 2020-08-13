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

//namespace rfk::generated
//{
//	Function const& getFunction123() noexcept
//	{
//		static Function f("methods", 123u, Type::getType<void>(), std::unique_ptr<NonMemberFunction<void()>>(new NonMemberFunction<void()>(&namespace3::functionInsideNamespace)), EFunctionFlags::Default);
//
//		return f; 
//	}
//} 

File_GENERATED 