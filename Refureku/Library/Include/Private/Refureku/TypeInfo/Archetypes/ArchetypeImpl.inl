/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline ArchetypeAPI::ArchetypeImpl::ArchetypeImpl(char const* name, std::size_t id, EEntityKind kind, std::size_t memorySize, EntityAPI const* outerEntity) noexcept:
	EntityAPI::EntityImpl(name, id, kind, outerEntity),
	_memorySize{memorySize}
{
}

inline EAccessSpecifier ArchetypeAPI::ArchetypeImpl::getAccessSpecifier() const noexcept
{
	return _accessSpecifier;
}

inline void ArchetypeAPI::ArchetypeImpl::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	_accessSpecifier = accessSpecifier;
}

inline std::size_t ArchetypeAPI::ArchetypeImpl::getMemorySize() const noexcept
{
	return _memorySize;
}