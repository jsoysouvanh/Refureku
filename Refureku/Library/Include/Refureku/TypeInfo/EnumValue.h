/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity.h"

namespace rfk
{
	class EnumValue final : public Entity
	{
		public:
			/** Value of this enum value. */
			int64	value = 0;

			EnumValue()														= delete;
			EnumValue(std::string&& name, uint64 id = 0u, int64 value = 0u)	noexcept;
			EnumValue(EnumValue const&)										= default;
			EnumValue(EnumValue&&)											= default;
			~EnumValue()													= default;
	};
}