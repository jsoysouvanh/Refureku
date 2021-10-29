/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline Enum::EnumImpl::EnumImpl(char const* name, std::size_t id, Archetype const* underlyingArchetype, Entity const* outerEntity) noexcept:
	ArchetypeImpl(name, id, EEntityKind::Enum, underlyingArchetype->getMemorySize(), outerEntity),
	_underlyingArchetype{*underlyingArchetype}
{
}

inline EnumValue& Enum::EnumImpl::addEnumValue(char const* name, std::size_t id, int64 value, Enum const*	backRef) noexcept
{
	return _enumValues.emplace_back(name, id, value, backRef);
}

inline void Enum::EnumImpl::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	_enumValues.reserve(capacity);
}

inline std::vector<EnumValue> const& Enum::EnumImpl::getEnumValues() const noexcept
{
	return _enumValues;
}

inline Archetype const& Enum::EnumImpl::getUnderlyingArchetype() const noexcept
{
	return _underlyingArchetype;
}