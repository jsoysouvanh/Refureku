/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestClass.h"

#include "Generated/TestFunctions.rfkh.h"

FUNCTION()
TestClass& func_return_noParam();

FUNCTION()
void func_noParam();

FUNCTION()
int func_return_singleParam(int i);

FUNCTION()
int func_return_MultipleParams(int i, int j);

FUNCTION()
void func_singleParam(int i);

FUNCTION()
void func_MultipleParams(int i, int j);

FUNCTION()
int func_overloaded();

FUNCTION()
int func_overloaded(int i);

File_TestFunctions_GENERATED