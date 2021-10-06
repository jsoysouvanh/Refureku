/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"
#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"

namespace rfk
{
	class EnumAPI::EnumImpl final : public ArchetypeAPI::ArchetypeImpl
	{
		private:
			/** Values contained in this enum. */
			std::vector<EnumValueAPI>	_enumValues;

			/** Underlying type of this enum. */
			ArchetypeAPI const&			_underlyingArchetype;

		public:
			inline EnumImpl(char const*			name,
							std::size_t			id,
							ArchetypeAPI const*	underlyingArchetype,
							Entity const*	outerEntity = nullptr)	noexcept;

			/**
			*	@brief Add an enum value to this enum.
			*	
			*	@param name		Name of the enum value.
			*	@param id		Unique entity id of the added enum value.
			*	@param value	Integer value of the enum value.
			*	@param backRef	Ref to the owner EnumAPI.
			*	
			*	@return The added enum value.
			*/
			inline EnumValueAPI&					addEnumValue(char const*	name,
																 std::size_t	id,
																 int64			value,
																 EnumAPI const*	backRef)			noexcept;

			/**
			*	@brief	Set the number of enum values for this entity.
			*			Useful to avoid reallocations when adding a lot of enum values.
			*			If the number of enum values is already >= to the provided capacity, this method has no effect.
			* 
			*	@param propertiesCapacity The number of enum values in this enum.
			*/
			inline void								setEnumValuesCapacity(std::size_t capacity)		noexcept;

			/**
			*	@brief Getter for the field _enumValues.
			* 
			*	@return _enumValues.
			*/
			inline std::vector<EnumValueAPI> const&	getEnumValues()							const	noexcept;

			/**
			*	@brief Getter for the field _underlyingArchetype.
			* 
			*	@return _underlyingArchetype.
			*/
			inline ArchetypeAPI const&				getUnderlyingArchetype()				const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/EnumImpl.inl"
}