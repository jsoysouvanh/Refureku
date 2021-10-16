/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestClass.h"
#include "NonReflectedClass.h"
#include "ConstructionTrackedClass.h"

#include "Generated/TestStaticFields.rfkh.h"

class ForwardDeclaredClass;

class CLASS() TestStaticFieldsClass
{
	public:
		FIELD()
		static int						intField;

		FIELD()
		static int const				constIntField;

		FIELD()
		static TestClass				testClassField;

		FIELD()
		static ForwardDeclaredClass*	forwardDeclaredClassField;

		FIELD()
		static NonReflectedClass		nonReflectedClassField;

		FIELD()
		static ConstructionTrackedClass	ctorTrackedClassField;

		FIELD()
		static ConstructionTrackedClass	const constCtorTrackedClassField;

	TestStaticFieldsClass_GENERATED
};

File_TestStaticFields_GENERATED