/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	class Archetype : public Entity
	{
		public:
			/**
			*	@brief Getter for the field _accessSpecifier.
			* 
			*	@return _accessSpecifier.
			*/
			RFK_NODISCARD REFUREKU_API EAccessSpecifier	getAccessSpecifier()			const	noexcept;

			/**
			*	@brief Getter for the field _memorySize.
			* 
			*	@return _memorySize.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t		getMemorySize()					const	noexcept;

			/**
			*	@brief Setter for the field _accessSpecifier.
			* 
			*	@param The access specifier to set.
			*/
			REFUREKU_API void							setAccessSpecifier(EAccessSpecifier)	noexcept;

		protected:
			//Forward declaration
			class ArchetypeImpl;

			REFUREKU_INTERNAL Archetype(ArchetypeImpl* implementation)	noexcept;
			REFUREKU_INTERNAL Archetype(Archetype&&)					noexcept;
			REFUREKU_INTERNAL ~Archetype()								noexcept;
	};
}