/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Entity/EntityImplementation.h"

namespace rfk
{
	class EnumValue final : public Entity
	{
		private:
			/** Value of this enum value. */
			int64	_value = 0;

		public:
			EnumValue(std::string&&	name,
					  std::size_t	id,
					  int64			value,
					  Entity const*	outerEntity = nullptr)	noexcept;

			/**
			*	@brief Cast the enum value as the provided template type.
			*
			*	@tparam T Type to cast the value to. Must be an integral type or an enum type.
			*
			*	@return The value contained in this enum value cast to T.
			*/
			template <typename T = int64, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
			T value() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/EnumValue.inl"
}