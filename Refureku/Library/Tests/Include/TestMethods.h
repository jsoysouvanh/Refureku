/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "TestClass.h"
#include "NonReflectedClass.h"

#include "Generated/TestMethods.rfkh.h"

class ForwardDeclaredClass;

class CLASS() TestMethodClass
{
	METHOD()
	void					noReturnNoParam();

	METHOD()
	int						returnIntNoParam();

	METHOD()
	int						returnIntParamInt(int i);

	METHOD()
	ForwardDeclaredClass*	returnFwdClassParamFwdClass(ForwardDeclaredClass* param);

	METHOD()
	NonReflectedClass&		returnNonReflectedNoParam(NonReflectedClass& param);

	METHOD()
	void					throwing();

	METHOD()
	void					constNoReturnNoParam() const;

	TestMethodClass_GENERATED
};

File_TestMethods_GENERATED