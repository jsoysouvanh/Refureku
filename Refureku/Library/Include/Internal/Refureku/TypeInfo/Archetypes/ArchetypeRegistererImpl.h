/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/DatabaseImpl.h"

namespace rfk
{
	class internal::ArchetypeRegistererImpl final
	{
		private:
			Archetype const& _registeredArchetype;

		public:
			inline ArchetypeRegistererImpl(Archetype const& archetype)	noexcept;
			inline ~ArchetypeRegistererImpl()								noexcept;

			/**
			*	@brief Getter for the field _registeredEntity.
			* 
			*	@return _registeredEntity.
			*/
			inline Archetype const& getRegisteredArchetype() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/ArchetypeRegistererImpl.inl"
}