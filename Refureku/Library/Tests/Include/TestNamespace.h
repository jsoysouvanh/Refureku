/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Generated/TestNamespace.rfkh.h"

namespace test_namespace NAMESPACE()
{
	FUNCTION()
	int func_nested_return_noParam();

	VARIABLE()
	extern int var_nested_extern;

	struct STRUCT() TestNamespaceNestedStruct
	{
		test_namespace_TestNamespaceNestedStruct_GENERATED
	};

	class CLASS() TestNamespaceNestedClass
	{
		test_namespace_TestNamespaceNestedClass_GENERATED
	};

	enum class ENUM() TestNamespaceNestedEnum
	{
		Value1,
		Value2
	};

	namespace nested_namespace NAMESPACE()
	{

	}
}

File_TestNamespace_GENERATED