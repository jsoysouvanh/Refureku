/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <stdexcept>	//std::logic_error

#include <Refureku/Properties/Instantiator.h>

#include "Generated/TestInstantiator.rfkh.h"

class CLASS() TestInstantiatorBase
{
	public:
		int value = 0;

		TestInstantiatorBase() = default;

		TestInstantiatorBase(int v):
			value{v}
		{}

	TestInstantiatorBase_GENERATED
};

class CLASS() TestInstantiator : public TestInstantiatorBase
{
	private:
		METHOD(rfk::Instantiator)
		static rfk::SharedPtr<TestInstantiator> defaultSharedInstantiator()
		{
			return rfk::makeShared<TestInstantiator>(1);
		}

		METHOD(rfk::Instantiator)
		static rfk::UniquePtr<TestInstantiator> defaultUniqueInstantiator()
		{
			return rfk::makeUnique<TestInstantiator>(2);
		}

		METHOD(rfk::Instantiator)
		RFK_NORETURN static rfk::UniquePtr<TestInstantiator> throwingUniqueInstantiator(int)
		{
			throw std::logic_error("Aww :(");
		}

	public:
		TestInstantiator(int v): TestInstantiatorBase(v)
		{}

	TestInstantiator_GENERATED
};

class CLASS() TestUniqueInstantiatorNotDefaultCtor : public TestInstantiatorBase
{
	private:
		METHOD(rfk::Instantiator)
		static rfk::UniquePtr<TestUniqueInstantiatorNotDefaultCtor> uniqueInstantiatorInt(int v)
		{
			return rfk::makeUnique<TestUniqueInstantiatorNotDefaultCtor>(v);
		}

		METHOD(rfk::Instantiator)
		static rfk::UniquePtr<TestUniqueInstantiatorNotDefaultCtor> uniqueInstantiatorIntInt(int v, int w)
		{
			return rfk::makeUnique<TestUniqueInstantiatorNotDefaultCtor>(v + w);
		}

	public:
		TestUniqueInstantiatorNotDefaultCtor(int v): TestInstantiatorBase(v)
		{}

	TestUniqueInstantiatorNotDefaultCtor_GENERATED
};

class CLASS() TestUniqueInstantiatorDefaultCtor : public TestInstantiatorBase
{
	public:
		TestUniqueInstantiatorDefaultCtor(): TestInstantiatorBase(0)
		{
		}

	TestUniqueInstantiatorDefaultCtor_GENERATED
};

class CLASS() TestSharedInstantiatorFallsbackToUniqueInstantiator : public TestInstantiatorBase
{
	private:
		METHOD(rfk::Instantiator)
		static rfk::UniquePtr<TestSharedInstantiatorFallsbackToUniqueInstantiator> uniqueInstantiatorInt(int v)
		{
			return rfk::makeUnique<TestSharedInstantiatorFallsbackToUniqueInstantiator>(v);
		}

		METHOD(rfk::Instantiator)
		static rfk::UniquePtr<TestSharedInstantiatorFallsbackToUniqueInstantiator> uniqueInstantiatorIntInt(int v, int w)
		{
			return rfk::makeUnique<TestSharedInstantiatorFallsbackToUniqueInstantiator>(v + w);
		}

	public:
		TestSharedInstantiatorFallsbackToUniqueInstantiator(int v): TestInstantiatorBase(v)
		{
		}

	TestSharedInstantiatorFallsbackToUniqueInstantiator_GENERATED
};

File_TestInstantiator_GENERATED