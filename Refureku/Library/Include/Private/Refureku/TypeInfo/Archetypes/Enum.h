/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

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
			std::vector<EnumValue>	_enumValues;

			/** Underlying type of this enum. */
			Archetype const&		_underlyingType;

		public:
			REFUREKU_API Enum(std::string&&		name,
							  std::size_t		id,
							  std::size_t		memorySize,
							  Archetype const*	underlyingType,
							  Entity const*		outerEntity = nullptr)	noexcept;

			/**
			*	@brief Retrieve from this enum an enum value matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching enum value.
			*	
			*	@return The first matching enum value if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, EnumValue const&>>>
			EnumValue const*							getEnumValue(Predicate predicate)		const	noexcept;

			/**
			*	@brief Retrieve from this enum all enum values matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching enum value.
			*	
			*	@return All the enum values matching with the given predicate.
			*/
			//TODO: Change std::vector dependency
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, EnumValue const&>>>
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
																	 std::size_t	entityId,
																	 int64			value)				noexcept;

			/**
			*	@brief	Set the number of enum values for this entity.
			*			Useful to avoid reallocations when adding a lot of enum values.
			*			If the number of enum values is already >= to the provided capacity, this method has no effect.
			* 
			*	@param propertiesCapacity The number of enum values in this enum.
			*/
			REFUREKU_API void							setEnumValuesCapacity(std::size_t capacity)		noexcept;

			/**
			*	@brief Get the enum value located at the provided index in the enum.
			* 
			*	@return The enum values at the provided index.
			* 
			*	@exception std::out_of_range if the provided index is greater or equal to the number of properties in this entity.
			*/
			REFUREKU_API EnumValue const&				getEnumValueAt(std::size_t valueIndex)	const;

			/**
			*	@brief Get the number of enum values contained in this enum.
			* 
			*	@return The number of enum values contained in this enum.
			*/
			REFUREKU_API std::size_t					getEnumValuesCount()					const	noexcept;

			/**
			*	@brief Getter for the field _underlyingType.
			* 
			*	@return _underlyingType.
			*/
			REFUREKU_API Archetype const&				getUnderlyingType()						const	noexcept;


			Enum& operator=(Enum const&)	= delete;
			Enum& operator=(Enum&&)			= delete;
	};

	/** Base implementation of getEnum, specialized for each reflected enum */
	template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
	rfk::Enum const* getEnum() noexcept;

	#include "Refureku/TypeInfo/Archetypes/Enum.inl"
}