/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	//Forward declaration
	class EnumValue;

	class Enum final : public Archetype
	{
		public:
			REFUREKU_API Enum(char const*		name,
							  std::size_t		id,
							  Archetype const*	underlyingArchetype,
							  Entity const*		outerEntity = nullptr)	noexcept;
			REFUREKU_API ~Enum()										noexcept;

			/**
			*	@brief Search an enum value by name in this enum.
			*
			*	@param name Name of the enum value to look for.
			*	
			*	@return The EnumValue having the provided name if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API
				EnumValue const*			getEnumValueByName(char const* name)						const	noexcept;

			/**
			*	@brief Search an enum value by value in this enum.
			*
			*	@param value Numerical value of the EnumValue to look for.
			*
			*	@return The first found EnumValue equals to the provided value if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API
				EnumValue const*			getEnumValue(int64 value)									const	noexcept;

			/**
			*	@brief Retrieve from this enum the first enum value matching with a given predicate.
			*
			*	@param predicate	Predicate returning true for any matching enum value.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return The first matching enum value if any is found, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				EnumValue const*			getEnumValueByPredicate(Predicate<EnumValue>	predicate,
																	void*					userData)	const;

			/**
			*	@brief Search all enum values in this enum holding the provided value.
			*
			*	@param value Numerical value of the EnumValues to look for.
			*
			*	@return All the EnumValues equal to the provided value.
			*/
			RFK_NODISCARD REFUREKU_API
				Vector<EnumValue const*>	getEnumValues(int64 value)									const	noexcept;

			/**
			*	@brief Retrieve from this enum all enum values matching with a given predicate.
			*
			*	@param predicate	Predicate returning true for any matching enum value.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return All the enum values matching with the given predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<EnumValue const*>	getEnumValuesByPredicate(Predicate<EnumValue>	predicate,
																	 void*					userData)	const;

			/**
			*	@brief	Get the enum value located at the provided index in the enum.
			*			If valueIndex is greater or equal to the enum values count, the behaviour is undefined.
			* 
			*	@param valueIndex Index of the enum value to get.
			* 
			*	@return The enum values at the provided index.
			*/
			RFK_NODISCARD REFUREKU_API 
				EnumValue const&			getEnumValueAt(std::size_t valueIndex)						const	noexcept;

			/**
			*	@brief Get the number of enum values contained in this enum.
			* 
			*	@return The number of enum values contained in this enum.
			*/
			RFK_NODISCARD REFUREKU_API 
				std::size_t					getEnumValuesCount()										const	noexcept;

			/**
			*	@brief Get the type this enum is based on.
			* 
			*	@return The type this enum is based on.
			*/
			RFK_NODISCARD REFUREKU_API 
				Archetype const&			getUnderlyingArchetype()									const	noexcept;

			/**
			*	@brief Execute the given visitor on all enum values in this enum.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API 
				bool						foreachEnumValue(Visitor<EnumValue>	visitor,
															 void*				userData)				const;

			/**
			*	@brief Add an enum value to this enum.
			*	
			*	@param name		Name of the enum value.
			*	@param id		Unique entity id of the added enum value.
			*	@param value	Integer value of the enum value.
			*	
			*	@return A pointer to the added enum value.
			*			If any of the parameters is unvalid, no enum value is added and nullptr is returned.
			*/
			REFUREKU_API 
				EnumValue*					addEnumValue(char const*	name,
														 std::size_t	id,
														 int64			value)									noexcept;

			/**
			*	@brief	Set the number of enum values for this entity.
			*			Useful to avoid reallocations when adding a lot of enum values.
			*			If the number of enum values is already >= to the provided capacity, this method has no effect.
			* 
			*	@param propertiesCapacity The number of enum values in this enum.
			*/
			REFUREKU_API
				void						setEnumValuesCapacity(std::size_t capacity)							noexcept;

		protected:
			//Forward declaration
			class EnumImpl;

			RFK_GEN_GET_PIMPL(EnumImpl, Entity::getPimpl())
	};

	/** Base implementation of getEnum, specialized for each reflected enum. */
	template <typename T>
	Enum const* getEnum() noexcept;

	REFUREKU_TEMPLATE_API(rfk::Allocator<Enum const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Enum const*, rfk::Allocator<Enum const*>>);

	#include "Refureku/TypeInfo/Archetypes/Enum.inl"
}