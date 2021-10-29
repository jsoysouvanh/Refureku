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
	class FundamentalArchetype final : public Archetype
	{
		public:
			REFUREKU_INTERNAL FundamentalArchetype(char const*	name,
												   std::size_t	id,
												   std::size_t	memorySize)	noexcept;
			REFUREKU_INTERNAL ~FundamentalArchetype()						noexcept;

		private:
			//Forward declaration
			class FundamentalArchetypeImpl;
	};
}