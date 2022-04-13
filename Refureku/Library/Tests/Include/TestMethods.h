/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <Refureku/Object.h>

#include "TestClass.h"
#include "NonReflectedClass.h"

#include "Generated/TestMethods.rfkh.h"

class ForwardDeclaredClass;

class CLASS() TestMethodClass : public rfk::Object
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

enum class EMethodTestCallResult
{
	NoInheritanceNPClass = 42,
	NoInheritanceNPClass2,
	NoInheritancePClass,
	SingleNPInheritanceNPClass,
	SingleNPInheritancePClass,
	SinglePInheritancePClass,
	MultiplePInheritanceNPClass,
	MultiplePInheritancePClassMethodOverride,
	MultipleNPInheritanceNPClass,
	MultipleNPInheritancePClass
};

class CLASS() NoInheritanceNPClass
{
	METHOD()
	EMethodTestCallResult methodNoInheritanceNPClass()
	{
		return EMethodTestCallResult::NoInheritanceNPClass;
	}

	NoInheritanceNPClass_GENERATED
};

class CLASS() SingleNPInheritanceNPClass : public NoInheritanceNPClass
{
	METHOD()
		EMethodTestCallResult methodSingleNPInheritanceNPClass()
	{
		return EMethodTestCallResult::SingleNPInheritanceNPClass;
	}

	SingleNPInheritanceNPClass_GENERATED
};

class CLASS() SingleNPInheritancePClass : public NoInheritanceNPClass
{
	METHOD()
	virtual EMethodTestCallResult methodSingleNPInheritancePClass()
	{
		return EMethodTestCallResult::SingleNPInheritancePClass;
	}

	METHOD()
	virtual EMethodTestCallResult methodSingleNPInheritancePClass2()
	{
		return EMethodTestCallResult::SingleNPInheritancePClass;
	}

	public:
		virtual ~SingleNPInheritancePClass() = default;

	SingleNPInheritancePClass_GENERATED
};

class CLASS() SinglePInheritancePClass : public SingleNPInheritancePClass
{
	METHOD()
	virtual EMethodTestCallResult methodSinglePInheritancePClass()
	{
		return EMethodTestCallResult::SinglePInheritancePClass;
	}

	virtual EMethodTestCallResult methodSingleNPInheritancePClass2() override
	{
		return EMethodTestCallResult::SinglePInheritancePClass;
	}

	SinglePInheritancePClass_GENERATED
};

class CLASS() NoInheritanceNPClass2
{
	METHOD()
	EMethodTestCallResult methodNoInheritanceNPClass2()
	{
		return EMethodTestCallResult::NoInheritanceNPClass2;
	}

	NoInheritanceNPClass2_GENERATED
};

class CLASS() NoInheritancePClass
{
	METHOD()
	virtual EMethodTestCallResult methodNoInheritancePClass()
	{
		return EMethodTestCallResult::NoInheritancePClass;
	}

	METHOD()
	virtual EMethodTestCallResult methodNoInheritancePClass2()
	{
		return EMethodTestCallResult::NoInheritancePClass;
	}

	METHOD()
	EMethodTestCallResult methodNoInheritancePClass3()
	{
		return EMethodTestCallResult::NoInheritancePClass;
	}

	METHOD()
	virtual EMethodTestCallResult methodNoInheritancePClass4()
	{
		return EMethodTestCallResult::NoInheritancePClass;
	}

	public:
		virtual ~NoInheritancePClass() = default;

	NoInheritancePClass_GENERATED
};

class CLASS() MultiplePInheritanceNPClass : public SinglePInheritancePClass, public NoInheritanceNPClass2
{
	METHOD()
	EMethodTestCallResult methodMultiplePInheritanceNPClass()
	{
		return EMethodTestCallResult::MultiplePInheritanceNPClass;
	}

	MultiplePInheritanceNPClass_GENERATED
};

class CLASS() MultiplePInheritancePClassMethodOverride : public SinglePInheritancePClass, public NoInheritancePClass
{
	METHOD()
	virtual EMethodTestCallResult methodMultiplePInheritancePClassMethodOverride()
	{
		return EMethodTestCallResult::MultiplePInheritancePClassMethodOverride;
	}

	virtual EMethodTestCallResult methodNoInheritancePClass() override
	{
		return EMethodTestCallResult::MultiplePInheritancePClassMethodOverride;
	}

	METHOD()
	virtual EMethodTestCallResult methodNoInheritancePClass2() override
	{
		return EMethodTestCallResult::MultiplePInheritancePClassMethodOverride;
	}

	MultiplePInheritancePClassMethodOverride_GENERATED
};

class CLASS() SinglePInheritancePClassLevel2 : public MultiplePInheritancePClassMethodOverride
{
	SinglePInheritancePClassLevel2_GENERATED
};

class CLASS() MultipleNPInheritanceNPClass : public NoInheritanceNPClass, public NoInheritanceNPClass2
{
	METHOD()
	EMethodTestCallResult methodMultipleNPInheritanceNPClass()
	{
		return EMethodTestCallResult::MultipleNPInheritanceNPClass;
	}

	MultipleNPInheritanceNPClass_GENERATED
};

class CLASS() MultipleNPInheritancePClass : public NoInheritanceNPClass, public NoInheritanceNPClass2
{
	METHOD()
	virtual EMethodTestCallResult methodMultipleNPInheritancePClass()
	{
		return EMethodTestCallResult::MultipleNPInheritancePClass;
	}

	MultipleNPInheritancePClass_GENERATED
};

//TODO: test with parent classes and/or child classes that are not reflected
//TODO: test with method overrides

File_TestMethods_GENERATED