/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"

namespace rfk
{
	class FundamentalArchetypeAPI final : public ArchetypeAPI
	{
		public:
			REFUREKU_INTERNAL FundamentalArchetypeAPI(char const*	name,
													  std::size_t	id,
													  std::size_t	memorySize)	noexcept;
			FundamentalArchetypeAPI(FundamentalArchetypeAPI&&)					= delete;
			REFUREKU_INTERNAL ~FundamentalArchetypeAPI()						noexcept;

		private:
			//Forward declaration
			class FundamentalArchetypeImpl;
	};
}