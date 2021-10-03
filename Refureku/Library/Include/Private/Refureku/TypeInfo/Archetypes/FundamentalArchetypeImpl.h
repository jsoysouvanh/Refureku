/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeAPI.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

namespace rfk
{
	class FundamentalArchetypeAPI::FundamentalArchetypeImpl final : public ArchetypeAPI::ArchetypeImpl
	{
		public:
			inline FundamentalArchetypeImpl(char const*	name,
											std::size_t	id,
											std::size_t	memorySize)	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeImpl.inl"
}