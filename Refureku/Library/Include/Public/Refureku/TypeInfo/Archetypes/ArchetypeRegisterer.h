/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/Pimpl.h"

namespace rfk
{
	//Forward declarations
	class Archetype;

	namespace internal
	{
		class ArchetypeRegistererImpl;
	}

	class ArchetypeRegisterer final
	{
		public:
			REFUREKU_API ArchetypeRegisterer(Archetype const& archetype)	noexcept;
			ArchetypeRegisterer(ArchetypeRegisterer const&)					= delete;
			ArchetypeRegisterer(ArchetypeRegisterer&&)						= delete;
			REFUREKU_API ~ArchetypeRegisterer()								noexcept;

		private:
			/** Pointer to ArchetypeRegisterer implementation. */
			Pimpl<internal::ArchetypeRegistererImpl> _pimpl;
	};
}