/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline FundamentalArchetype::FundamentalArchetypeImpl::FundamentalArchetypeImpl(char const* name, std::size_t id, std::size_t memorySize) noexcept:
	ArchetypeImpl(name, id, EEntityKind::FundamentalArchetype, memorySize)
{
}