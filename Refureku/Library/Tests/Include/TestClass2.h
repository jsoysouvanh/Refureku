/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestClass.h"

#include "Generated/TestClass2.rfkh.h"

class CLASS(UniqueInheritedPropertyChild(1), MultipleInheritedPropertyChild(3)) TestClass2 : public TestClass
{
	TestClass2_GENERATED
};


class CLASS(MultipleInheritedPropertyChild(5), UniqueInheritedProperty(6)) TestClass3 : public TestClass
{
	TestClass3_GENERATED
};

File_TestClass2_GENERATED