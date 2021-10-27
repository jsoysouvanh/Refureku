/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Generated/TestNamespace.rfkh.h"

namespace test_namespace NAMESPACE()
{
	FUNCTION()
	int func_nested_return_noParam();

	FUNCTION()
	inline int func_nested_overload() { return 0; };

	FUNCTION()
	static inline int func_nested_overload(int i) { return i; }

	VARIABLE()
	extern int var_nested_extern;

	struct STRUCT() TestNamespaceNestedStruct
	{
		test_namespace_TestNamespaceNestedStruct_GENERATED
	};

	struct STRUCT() TestNamespaceNestedStruct2
	{
		test_namespace_TestNamespaceNestedStruct2_GENERATED
	};

	class CLASS() TestNamespaceNestedClass
	{
		test_namespace_TestNamespaceNestedClass_GENERATED
	};

	class CLASS() TestNamespaceNestedClass2
	{
		test_namespace_TestNamespaceNestedClass2_GENERATED
	};

	class CLASS() TestNamespaceNestedClass3
	{
		test_namespace_TestNamespaceNestedClass3_GENERATED
	};

	enum class ENUM() TestNamespaceNestedEnum
	{
		Value1,
		Value2
	};

	namespace nested_namespace NAMESPACE()
	{

	}

	namespace nested_namespace2 NAMESPACE()
	{

	}
}

File_TestNamespace_GENERATED