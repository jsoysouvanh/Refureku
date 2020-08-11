/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class FundamentalArchetype final : public Archetype
	{
		public:
			FundamentalArchetype()								= delete;
			FundamentalArchetype(std::string&&	name,
								 uint64			id,
								 uint64			memorySize)		noexcept;
			FundamentalArchetype(FundamentalArchetype const&)	= delete;
			FundamentalArchetype(FundamentalArchetype&&)		= delete;
			~FundamentalArchetype()								= default;
	};
}