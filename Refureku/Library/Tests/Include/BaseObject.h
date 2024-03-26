/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <stdexcept>	//std::logic_error

#include <Refureku/Object.h>
#include <Refureku/Properties/Instantiator.h>

#include "TestClass.h"

#include "Generated/BaseObject.rfkh.h"

class CLASS() BaseObject : public rfk::Object
{
	private:
		FIELD()
		int _i;

		METHOD(rfk::Instantiator)
		static rfk::SharedPtr<BaseObject> customInstantiator(int i) noexcept
		{
			return rfk::SharedPtr<BaseObject>(new BaseObject(i), [](BaseObject* ptr)
											   {
												   //Use some custom deleter...
												   delete ptr;
											   });
		}

		METHOD(rfk::Instantiator)
		/**RFK_NORETURN*/ static rfk::SharedPtr<BaseObject> customInstantiator2Params(int, int)
		{
			throw std::logic_error("Error");
		}

	public:
		BaseObject(int i) noexcept:
			_i{i}
		{
		}

		METHOD()
		int getI() const noexcept
		{
			return _i;
		}

	BaseObject_GENERATED
};

class CLASS() ObjectDerived1 : public BaseObject
{
	private:
		FIELD()
		int j;

		METHOD(rfk::Instantiator)
		static rfk::SharedPtr<ObjectDerived1> customInstantiator() noexcept
		{
			return rfk::makeShared<ObjectDerived1>(1);
		}

	public:
		using BaseObject::BaseObject;

	ObjectDerived1_GENERATED
};

class CLASS() ObjectDerived2 : public BaseObject
{
	public:
		ObjectDerived2() noexcept:
			BaseObject(2)
		{
		}

	ObjectDerived2_GENERATED
};

class CLASS() ObjectDerivedDerived : public ObjectDerived1
{
	ObjectDerivedDerived_GENERATED
};

class CLASS() MultipleInheritanceClass : public ObjectDerived2, public TestClass
{
	MultipleInheritanceClass_GENERATED
};

File_BaseObject_GENERATED