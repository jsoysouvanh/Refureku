/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"

namespace rfk
{
	class EnumValueAPI::EnumValueImpl final : public Entity::EntityImpl
	{
		private:
			/** Value of this enum value. */
			int64	_value = 0;

		public:
			inline EnumValueImpl(char const*		name,
								 std::size_t		id,
								 int64				value,
								 Entity const*	outerEntity = nullptr)	noexcept;

			/**
			*	@brief Getter for the field _value.
			*
			*	@return _value.
			*/
			inline int64 getValue() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/EnumValueImpl.inl"
}