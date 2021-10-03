/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline EnumAPI::EnumImpl::EnumImpl(char const* name, std::size_t id, ArchetypeAPI const* underlyingArchetype, EntityAPI const* outerEntity) noexcept:
	ArchetypeImpl(name, id, EEntityKind::Enum, underlyingArchetype->getMemorySize(), outerEntity),
	_underlyingArchetype{*underlyingArchetype}
{
}

inline EnumValueAPI& EnumAPI::EnumImpl::addEnumValue(char const* name, std::size_t id, int64 value, EnumAPI const*	backRef) noexcept
{
	return _enumValues.emplace_back(name, id, value, backRef);
}

inline void EnumAPI::EnumImpl::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	_enumValues.reserve(capacity);
}

inline std::vector<EnumValueAPI> const& EnumAPI::EnumImpl::getEnumValues() const noexcept
{
	return _enumValues;
}

inline ArchetypeAPI const& EnumAPI::EnumImpl::getUnderlyingArchetype() const noexcept
{
	return _underlyingArchetype;
}