/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Object.h"

#include "Generated/TestCast.rfkh.h"

class CLASS() Base : public rfk::Object
{
	public:
		virtual ~Base() = default;

	Base_GENERATED
};

class CLASS() NonVirtualBase
{
	NonVirtualBase_GENERATED
};

class CLASS() Child1 : public Base
{
	Child1_GENERATED
};

class CLASS() Child2 : public Base
{
	Child2_GENERATED
};

class CLASS() GrandChild1 : public Child1
{
	GrandChild1_GENERATED
};

class CLASS() GrandChild2 : public Child2
{
	GrandChild2_GENERATED
};

class CLASS() Base2 : public rfk::Object
{
	public:
		virtual ~Base2() = default;

	Base2_GENERATED
};

class CLASS() Child3 : public Child1, public Base2
{
	Child3_GENERATED
};

class CLASS() Child4 : public Child1, public NonVirtualBase
{
	Child4_GENERATED
};

//======================================

class CLASS() NotObjectBase
{
	public:
		virtual ~NotObjectBase() = default;

	NotObjectBase_GENERATED
};

class CLASS() NotObjectChild1 : public NotObjectBase
{
	NotObjectChild1_GENERATED
};

//======================================

/**
* /!\ VIRTUAL INHERITANCE IS NOT SUPPORTED /!\

class CLASS() Child1Virtual : public Base
{
	Child1Virtual_GENERATED
};

class CLASS() Child2Virtual : public Base
{
	Child2Virtual_GENERATED
};

class CLASS() GrandChildVirtual : public Child1Virtual, public Child2Virtual
{
	GrandChildVirtual_GENERATED
};

*/

File_TestCast_GENERATED