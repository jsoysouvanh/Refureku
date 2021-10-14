/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestProperties.h"

#include "Generated/TestEnum.rfkh.h"

enum ENUM() TestEnum
{
	TestEnumValue1 ENUMVALUE(BaseTestProperty(0)),
	TestEnumValue2,
	TestEnumValue3
};

enum class ENUM() TestEnumClass : char
{
	Value1 = 1 << 0,
	Value2 = 1 << 1,
	Value3 = 1 << 2,
	Value3Alias = Value3,
	Value123 = Value1 | Value2 | Value3
};

File_TestEnum_GENERATED