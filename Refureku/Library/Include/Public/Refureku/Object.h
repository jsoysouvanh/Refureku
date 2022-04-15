/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"

namespace rfk
{
	//Forward declaration
	class Struct;

	/**
	*	Base class which implements the virtual getArchetype method.
	*/
	class REFUREKU_API Object
	{
		public:
			Object()				= default;
			Object(Object const&)	= default;
			Object(Object&&)		= default;
			virtual ~Object()		= default;

			virtual Struct const& getArchetype() const noexcept = 0;
			
			Object& operator=(Object const&)	= default;
			Object& operator=(Object&&)			= default;
	};
}