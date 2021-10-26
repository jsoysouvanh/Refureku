/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "TestClass.h"
#include "NonReflectedClass.h"

#include "Generated/TestFunctions.rfkh.h"

class ForwardDeclaredClass;

FUNCTION()
TestClass& func_return_noParam();

FUNCTION()
static void func_static_noParam() {};

FUNCTION()
void func_noParam();

FUNCTION()
int func_return_singleParam(int i);

FUNCTION()
int func_return_MultipleParams(int i, int j);

FUNCTION()
void func_singleParam(int i);

FUNCTION()
void func_MultipleParams(int, int);

FUNCTION()
int func_overloaded();

FUNCTION()
int func_overloaded(int i);

FUNCTION()
void func_noParam_throwLogicError();

FUNCTION()
inline void func_inline_noParam(){}

FUNCTION()
NonReflectedClass func_returnNonReflected_noParam();

FUNCTION()
void func_twoParamsNonReflected(NonReflectedClass& param, int value);

FUNCTION()
ForwardDeclaredClass& func_return_oneParam_forwardDeclared(ForwardDeclaredClass& param);

File_TestFunctions_GENERATED