/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Utility/Pimpl.h"

namespace rfk
{
	//Forward declarations
	class ArchetypeAPI;

	namespace internal
	{
		class ArchetypeRegistererImpl;
	}

	class ArchetypeRegistererAPI final
	{
		public:
			REFUREKU_API ArchetypeRegistererAPI(ArchetypeAPI const& archetype)	noexcept;
			ArchetypeRegistererAPI(ArchetypeRegistererAPI const&)				= delete;
			ArchetypeRegistererAPI(ArchetypeRegistererAPI&&)					= delete;
			REFUREKU_API ~ArchetypeRegistererAPI()								noexcept;

		private:
			Pimpl<internal::ArchetypeRegistererImpl> _pimpl;
	};
}