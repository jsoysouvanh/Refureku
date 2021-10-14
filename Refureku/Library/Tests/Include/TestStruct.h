/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Generated/TestStruct.rfkh.h"

struct STRUCT() TestStruct
{
	class CLASS() NestedClass
	{
		TestStruct_NestedClass_GENERATED
	};

	struct STRUCT() NestedStruct
	{
		TestStruct_NestedStruct_GENERATED
	};

	TestStruct_GENERATED
};

File_TestStruct_GENERATED