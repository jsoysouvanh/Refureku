/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	class Archetype;	//Forward declaration

	class ArchetypeRegisterer
	{
		private:
			/** Registered archetype. */
			Archetype const& _registeredArchetype;

		public:
			ArchetypeRegisterer()							= delete;
			ArchetypeRegisterer(Archetype const& archetype)	noexcept;
			ArchetypeRegisterer(ArchetypeRegisterer const&)	= delete;
			ArchetypeRegisterer(ArchetypeRegisterer&&)		= delete;
			~ArchetypeRegisterer()							noexcept;

			ArchetypeRegisterer& operator=(ArchetypeRegisterer const&)	= delete;
			ArchetypeRegisterer& operator=(ArchetypeRegisterer&&)		= delete;
	};
}