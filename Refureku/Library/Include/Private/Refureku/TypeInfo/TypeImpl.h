/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Type.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class Type::TypeImpl
	{
		private:
			/** Parts of this type. */
			std::vector<TypePart>	_parts;

			/** Archetype of this type. */
			Archetype const*		_archetype = nullptr;

		public:
			/**
			*	@brief Add a default-constructed type part to this type.
			* 
			*	@return The newly constructed type part.
			*/
			inline TypePart&						addTypePart()								noexcept;


			/**
			*	@brief Reallocate the underlying dynamic memory to use no more than needed.
			*/
			inline void								optimizeMemory()							noexcept;

			/**
			*	@brief Getter for the field _parts.
			* 
			*	@return _parts.
			*/
			inline std::vector<TypePart> const&	getParts()							const	noexcept;

			/**
			*	@brief Getter for the field _archetype.
			* 
			*	@return _archetype.
			*/
			inline Archetype const*				getArchetype()						const	noexcept;

			/**
			*	@brief Setter for the field _archetype.
			* 
			*	@param archetype The archetype to set.
			*/
			inline void								setArchetype(Archetype const* archetype)	noexcept;
	};

	#include "Refureku/TypeInfo/TypeImpl.inl"
}