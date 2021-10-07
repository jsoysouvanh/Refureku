/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/Containers/Vector.h"

namespace rfk
{
	class EnumValue final : public Entity
	{
		public:
			EnumValue(char const*		name,
						 std::size_t		id,
						 int64				value,
						 Entity const*	outerEntity = nullptr)	noexcept;
			EnumValue(EnumValue&&)							noexcept;
			~EnumValue()											noexcept;

			/**
			*	@brief Cast the enum value as the provided template type.
			*
			*	@tparam T Type to cast the value to. Must be an integral type or an enum type.
			*
			*	@return The value contained in this enum value cast to T.
			*/
			template <typename T = int64, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
			RFK_NODISCARD T						getValue()	const	noexcept;

			/**
			*	@brief Get the enum value as an int64.
			*
			*	@return The enum value as an int64.
			*/
			RFK_NODISCARD REFUREKU_API int64	getValue()	const	noexcept;

		protected:
			//Forward declaration
			class EnumValueImpl;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<EnumValue const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<EnumValue const*, rfk::Allocator<EnumValue const*>>);

	#include "Refureku/TypeInfo/Archetypes/EnumValue.inl"
}