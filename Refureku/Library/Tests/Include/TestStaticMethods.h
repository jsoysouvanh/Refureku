/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestClass.h"
#include "NonReflectedClass.h"

#include "Generated/TestStaticMethods.rfkh.h"

class ForwardDeclaredClass;

class CLASS() TestStaticMethodClass
{
	METHOD()
	static void						noReturnNoParam();

	METHOD()
	static int						returnIntNoParam();

	METHOD()
	static int						returnIntParamInt(int i);

	METHOD()
	static ForwardDeclaredClass*	returnFwdClassParamFwdClass(ForwardDeclaredClass* param);

	METHOD()
	static NonReflectedClass&		returnNonReflectedNoParam(NonReflectedClass& param);

	METHOD()
	static void						throwing();

	TestStaticMethodClass_GENERATED
};

File_TestStaticMethods_GENERATED