/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/TypeInfo/Entity/Entity.h"

namespace rfk
{
	class EnumValue final : public Entity
	{
		public:
			/** Value of this enum value. */
			int64	value = 0;

			EnumValue()												= delete;
			EnumValue(std::string&& name, uint64 id, int64 value)	noexcept;
			EnumValue(EnumValue const&)								= delete;
			EnumValue(EnumValue&&)									= delete;
			~EnumValue()											= default;

			/**
			*	@brief Cast the enum value as the provided template type.
			*
			*	@tparam T Type to cast the value to. Must be an integral type or an enum type.
			*
			*	@return The value contained in this enum value cast to T.
			*/
			template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
			T as() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/EnumValue.inl"
}