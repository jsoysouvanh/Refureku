/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"

namespace rfk
{
	class Archetype;	//Forward declaration

	class ArchetypeRegisterer
	{
		private:
			/** Registered archetype. */
			Archetype const& _registeredArchetype;

		public:
			REFUREKU_API ArchetypeRegisterer()								= delete;
			REFUREKU_API ArchetypeRegisterer(Archetype const& archetype)	noexcept;
			REFUREKU_API ArchetypeRegisterer(ArchetypeRegisterer const&)	= delete;
			REFUREKU_API ArchetypeRegisterer(ArchetypeRegisterer&&)			= delete;
			REFUREKU_API ~ArchetypeRegisterer()								noexcept;

			REFUREKU_API ArchetypeRegisterer& operator=(ArchetypeRegisterer const&)	= delete;
			REFUREKU_API ArchetypeRegisterer& operator=(ArchetypeRegisterer&&)		= delete;
	};
}