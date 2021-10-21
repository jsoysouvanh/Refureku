/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

class BaseObjectWithoutVirtualDtor
{

};

class BaseObjectWithoutVirtualDtorDerived : public BaseObjectWithoutVirtualDtor
{
};

class BaseObjectWithVirtualDtor
{
	public:
		virtual ~BaseObjectWithVirtualDtor() = default;
};

class BaseObjectWithVirtualDtorDerived : public BaseObjectWithVirtualDtor
{
};

#include <memory>

#include <Refureku/Properties/Instantiator.h>

#include "Generated/TestUniquePtr.rfkh.h"

class CLASS() InstantiatorPropertyCheck
{
	METHOD()
	std::shared_ptr<InstantiatorPropertyCheck> customInt()
	{
		return std::shared_ptr<InstantiatorPropertyCheck>(new InstantiatorPropertyCheck(), [](InstantiatorPropertyCheck* ptr)
														  {
															  delete ptr;
														  });
	}

	InstantiatorPropertyCheck_GENERATED
};

File_TestUniquePtr_GENERATED