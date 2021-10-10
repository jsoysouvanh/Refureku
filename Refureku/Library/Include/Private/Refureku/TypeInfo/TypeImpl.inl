/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline TypePart& Type::TypeImpl::addTypePart() noexcept
{
	return _parts.emplace_back();
}

inline void Type::TypeImpl::optimizeMemory() noexcept
{
	_parts.shrink_to_fit();
}

inline std::vector<TypePart> const& Type::TypeImpl::getParts() const noexcept
{
	return _parts;
}

inline Archetype const* Type::TypeImpl::getArchetype() const noexcept
{
	return _archetype;
}

inline void Type::TypeImpl::setArchetype(Archetype const* archetype) noexcept
{
	_archetype = archetype;
}