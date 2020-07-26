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

#include "TypeInfo/Archetypes/Archetype.h"
#include "TypeInfo/EnumValue.h"

namespace rfk
{
	class Enum : public Archetype
	{
		public:
			/** Values contained in this enum */
			std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName>	values;

			Enum()													= delete;
			Enum(std::string&& name, uint64 id, uint64 memorySize)	noexcept;
			Enum(Enum const&)										= delete;
			Enum(Enum&&)											= default;
			~Enum()													= default;

			/**
			*	@return The EnumValue corresponding to the provided name if any, else nullptr
			*/
			EnumValue const*					getEnumValue(std::string enumValueName)	const noexcept;
			
			/**
			*	@return The first found EnumValue equals to the provided value if any, else nullptr
			*/
			EnumValue const*					getEnumValue(int64 value)				const noexcept;

			/**
			*	@return All the EnumValues equal to the provided value
			*/
			std::vector<EnumValue const*>	getEnumValues(int64 value)					const noexcept;

			Enum& operator=(Enum const&)	= delete;
			Enum& operator=(Enum&&)			= default;
	};

	/** Base implementation of getEnum, specialized for each reflected enum */
	template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
	inline rfk::Enum const* getEnum() noexcept
	{
		return nullptr;
	}
}