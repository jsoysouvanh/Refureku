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

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"

namespace rfk
{
	//Forward declaration
	class Type;

	class Enum final : public Archetype
	{
		private:
			/** Values contained in this enum. */
			std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName>	_values;

			/** Underlying type of this enum. */
			Archetype const&														_underlyingType;

		public:
			REFUREKU_API Enum()											= delete;
			REFUREKU_API Enum(std::string&&		name,
							  std::size_t		id,
							  uint64			memorySize,
							  Archetype const*	underlyingType,
							  Entity const*		outerEntity = nullptr)	noexcept;
			REFUREKU_API Enum(Enum const&)								= delete;
			REFUREKU_API Enum(Enum&&)									= delete;
			REFUREKU_API ~Enum()										= default;

			/**
			*	@brief Retrieve from this enum an enum value matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching enum value.
			*	
			*	@return The first matching enum value if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, EnumValue const*>>>
			EnumValue const*							getEnumValue(Predicate predicate)		const	noexcept;

			/**
			*	@brief Retrieve from this enum all enum values matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching enum value.
			*	
			*	@return All the enum values matching with the given predicate.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, EnumValue const*>>>
			std::vector<EnumValue const*>				getEnumValues(Predicate predicate)		const	noexcept;

			/**
			*	@brief Search an enum value in this enum.
			*
			*	@param enumValueName Name of the enum value to search for.
			*	
			*	@return The EnumValue corresponding to the provided name if any, else nullptr.
			*/
			REFUREKU_API EnumValue const*				getEnumValue(std::string enumValueName)	const	noexcept;
			
			/**
			*	@brief Search an enum value in this enum.
			*
			*	@param value Numerical value of the EnumValue to look for.
			*
			*	@return The first found EnumValue equals to the provided value if any, else nullptr.
			*/
			REFUREKU_API EnumValue const*				getEnumValue(int64 value)				const	noexcept;

			/**
			*	@brief Search all enum values in this enum holding the provided value.
			*
			*	@param value Numerical value of the EnumValues to look for.
			*
			*	@return All the EnumValues equal to the provided value.
			*/
			REFUREKU_API std::vector<EnumValue const*>	getEnumValues(int64 value)				const	noexcept;

			/**
			*	@brief Add an enum value to this enum.
			*	
			*	@param enumValueName	Name of the enum value.
			*	@param entityId			Unique entity id of the added enum value.
			*	@param value			Integer value of the enum value.
			*	
			*	@return A pointer to the added enum value. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the enum value **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API EnumValue*						addEnumValue(std::string	enumValueName,
																	 uint64			entityId,
																	 int64			value)				noexcept;

			/**
			*	@brief Getter for the field _values.
			* 
			*	@return _values.
			*/
			REFUREKU_API std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName> const&	getEnumValues()		const	noexcept;

			/**
			*	@brief Non-const getter for the field _values.
			* 
			*	@return _values.
			*/
			REFUREKU_API std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName>&			getEnumValues()				noexcept;

			/**
			*	@brief Getter for the field _underlyingType.
			* 
			*	@return _underlyingType.
			*/
			REFUREKU_API Archetype const&																getUnderlyingType()	const	noexcept;
	};

	/** Base implementation of getEnum, specialized for each reflected enum */
	template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
	rfk::Enum const* getEnum() noexcept;

	#include "Refureku/TypeInfo/Archetypes/Enum.inl"
}