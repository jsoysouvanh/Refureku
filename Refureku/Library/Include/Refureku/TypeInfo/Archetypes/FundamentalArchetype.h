/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class FundamentalArchetype final : public Archetype
	{
		public:
			FundamentalArchetype(std::string&&	name,
								 std::size_t	id,
								 std::size_t	memorySize)		noexcept;
			FundamentalArchetype(FundamentalArchetype const&)	= delete;
			FundamentalArchetype(FundamentalArchetype&&)		= delete;
	};
}