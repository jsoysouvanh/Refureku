/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline TypePartAPI& TypeAPI::TypeImpl::addTypePart() noexcept
{
	return _parts.emplace_back();
}

inline void TypeAPI::TypeImpl::optimizeMemory() noexcept
{
	_parts.shrink_to_fit();
}

inline std::vector<TypePartAPI> const& TypeAPI::TypeImpl::getParts() const noexcept
{
	return _parts;
}

inline ArchetypeAPI const* TypeAPI::TypeImpl::getArchetype() const noexcept
{
	return _archetype;
}

inline void TypeAPI::TypeImpl::setArchetype(ArchetypeAPI const* archetype) noexcept
{
	_archetype = archetype;
}