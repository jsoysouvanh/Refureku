/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"
#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"

namespace rfk
{
	/**
	*	@brief Predicate defining if an enum value is valid or not.
	* 
	*	@param prop		The tested enum value.
	*	@param userData	Data received from the user.
	*/
	using EnumValuePredicate = bool (*)(EnumValueAPI const& value, void* userData);

	class EnumAPI final : public ArchetypeAPI
	{
		public:
			REFUREKU_API EnumAPI(char const*			name,
								 std::size_t			id,
								 ArchetypeAPI const*	underlyingArchetype,
								 EntityAPI const*		outerEntity = nullptr)	noexcept;
			REFUREKU_API ~EnumAPI()												noexcept;

			/**
			*	@brief Add an enum value to this enum.
			*	
			*	@param name		Name of the enum value.
			*	@param id		Unique entity id of the added enum value.
			*	@param value	Integer value of the enum value.
			*	
			*	@return A pointer to the added enum value.
			*/
			REFUREKU_API EnumValueAPI*								addEnumValue(char const*	name,
																				 std::size_t	id,
																				 int64			value)												noexcept;
			
			/**
			*	@brief	Set the number of enum values for this entity.
			*			Useful to avoid reallocations when adding a lot of enum values.
			*			If the number of enum values is already >= to the provided capacity, this method has no effect.
			* 
			*	@param propertiesCapacity The number of enum values in this enum.
			*/
			REFUREKU_API void										setEnumValuesCapacity(std::size_t capacity)										noexcept;

			/**
			*	@brief Search an enum value by name in this enum.
			*
			*	@param name Name of the enum value to look for.
			*	
			*	@return The EnumValue having the provided name if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API EnumValueAPI const*			getEnumValueByName(char const* name)									const	noexcept;

			/**
			*	@brief Search an enum value by value in this enum.
			*
			*	@param value Numerical value of the EnumValue to look for.
			*
			*	@return The first found EnumValue equals to the provided value if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API EnumValueAPI const*			getEnumValue(int64 value)												const	noexcept;

			/**
			*	@brief Retrieve from this enum an enum value matching with a given predicate.
			*
			*	@param predicate	Predicate returning true for any matching enum value.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return The first matching enum value if any is found, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API EnumValueAPI const*			getEnumValueByPredicate(EnumValuePredicate predicate,
																							void*			   userData = nullptr)	const	noexcept;

			/**
			*	@brief Search all enum values in this enum holding the provided value.
			*
			*	@param value Numerical value of the EnumValues to look for.
			*
			*	@return All the EnumValues equal to the provided value.
			*/
			RFK_NODISCARD REFUREKU_API Vector<EnumValueAPI const*>	getEnumValues(int64 value)										const	noexcept;

			/**
			*	@brief Retrieve from this enum all enum values matching with a given predicate.
			*
			*	@param predicate	Predicate returning true for any matching enum value.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return All the enum values matching with the given predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<EnumValueAPI const*>	getEnumValuesByPredicate(EnumValuePredicate predicate,
																							 void*				userData = nullptr)	const	noexcept;

			/**
			*	@brief	Get the enum value located at the provided index in the enum.
			*			If valueIndex is greater or equal to the enum values count, the behaviour is undefined.
			* 
			*	@param valueIndex Index of the enum value to get.
			* 
			*	@return The enum values at the provided index.
			*/
			RFK_NODISCARD REFUREKU_API EnumValueAPI const&			getEnumValueAt(std::size_t valueIndex)							const	noexcept;

			/**
			*	@brief Get the number of enum values contained in this enum.
			* 
			*	@return The number of enum values contained in this enum.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t					getEnumValuesCount()											const	noexcept;

			/**
			*	@brief Getter for the field _underlyingArchetype.
			* 
			*	@return _underlyingArchetype.
			*/
			RFK_NODISCARD REFUREKU_API ArchetypeAPI const&			getUnderlyingArchetype()										const	noexcept;

		protected:
			//Forward declaration
			class EnumImpl;
	};

	/** Base implementation of getEnum, specialized for each reflected enum */
	//TODO
	//template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
	//rfk::EnumAPI const* getEnum() noexcept;
}