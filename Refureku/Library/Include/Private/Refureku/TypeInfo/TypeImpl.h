/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/TypeAPI.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"

namespace rfk
{
	class TypeAPI::TypeImpl
	{
		private:
			/** Parts of this type. */
			std::vector<TypePartAPI>	_parts;

			/** Archetype of this type. */
			ArchetypeAPI const*			_archetype = nullptr;

		public:
			/**
			*	@brief Add a default-constructed type part to this type.
			* 
			*	@return The newly constructed type part.
			*/
			inline TypePartAPI&						addTypePart()								noexcept;


			/**
			*	@brief Reallocate the underlying dynamic memory to use no more than needed.
			*/
			inline void								optimizeMemory()							noexcept;

			/**
			*	@brief Getter for the field _parts.
			* 
			*	@return _parts.
			*/
			inline std::vector<TypePartAPI> const&	getParts()							const	noexcept;

			/**
			*	@brief Getter for the field _archetype.
			* 
			*	@return _archetype.
			*/
			inline ArchetypeAPI const*				getArchetype()						const	noexcept;

			/**
			*	@brief Setter for the field _archetype.
			* 
			*	@param archetype The archetype to set.
			*/
			inline void								setArchetype(ArchetypeAPI const* archetype)	noexcept;
	};

	#include "Refureku/TypeInfo/TypeImpl.inl"
}