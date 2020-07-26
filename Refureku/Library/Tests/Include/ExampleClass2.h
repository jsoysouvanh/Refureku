#pragma once

#include "Generated/ExampleClass2.rfk.h"

namespace namespace3 RFKNamespace()
{
	class RFKClass() AnotherClassInNamespace3
	{

		AnotherClassInNamespace3_GENERATED
	};
}

namespace test1::test2 RFKNamespace()
{
	enum class RFKEnum() NestedEnumInNestedNamespace : rfk::uint8
	{
		SomeValue = 42u
	};
}

File_GENERATED