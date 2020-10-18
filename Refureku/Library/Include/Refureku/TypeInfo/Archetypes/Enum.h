/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"

namespace rfk
{
	//Forward declaration
	class Type;

	class Enum final : public Archetype
	{
		public:
			/** Values contained in this enum. */
			std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName>	values;

			/** Underlying type of this enum. */
			Type const&																underlyingType;

			Enum()								= delete;
			Enum(std::string&&	name,
				 uint64			id,
				 uint64			memorySize,
				 Type const&	underlyingType)	noexcept;
			Enum(Enum const&)					= delete;
			Enum(Enum&&)						= delete;
			~Enum()								= default;

			/**
			*	@brief Search an enum value in this enum.
			*
			*	@param enumValueName Name of the enum value to search for.
			*	
			*	@return The EnumValue corresponding to the provided name if any, else nullptr.
			*/
			EnumValue const*				getEnumValue(std::string enumValueName)	const noexcept;
			
			/**
			*	@brief Search an enum value in this enum.
			*
			*	@param value Numerical value of the EnumValue to look for.
			*
			*	@return The first found EnumValue equals to the provided value if any, else nullptr.
			*/
			EnumValue const*				getEnumValue(int64 value)				const noexcept;

			/**
			*	@brief Search all enum values in this enum holding the provided value.
			*
			*	@param value Numerical value of the EnumValues to look for.

			*	@return All the EnumValues equal to the provided value.
			*/
			std::vector<EnumValue const*>	getEnumValues(int64 value)				const noexcept;
	};

	/** Base implementation of getEnum, specialized for each reflected enum */
	template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
	inline rfk::Enum const* getEnum() noexcept;

	#include "Refureku/TypeInfo/Archetypes/Enum.inl"
}