/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline Archetype::ArchetypeImpl::ArchetypeImpl(char const* name, std::size_t id, EEntityKind kind, std::size_t memorySize, Entity const* outerEntity) noexcept:
	Entity::EntityImpl(name, id, kind, outerEntity),
	_accessSpecifier{EAccessSpecifier::Undefined},
	_memorySize{memorySize}
{
}

inline EAccessSpecifier Archetype::ArchetypeImpl::getAccessSpecifier() const noexcept
{
	return _accessSpecifier;
}

inline void Archetype::ArchetypeImpl::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	_accessSpecifier = accessSpecifier;
}

inline std::size_t Archetype::ArchetypeImpl::getMemorySize() const noexcept
{
	return _memorySize;
}