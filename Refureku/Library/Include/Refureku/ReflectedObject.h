/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	class ReflectedObject
	{
		public:
		ReflectedObject()						= default;
		ReflectedObject(ReflectedObject const&) = default;
		ReflectedObject(ReflectedObject&&)		= default;
		virtual ~ReflectedObject()				= default;

		virtual	Struct const& getArchetype()	const noexcept = 0;
	};
}