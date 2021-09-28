#include "Refureku/TypeInfo/Archetypes/EnumImpl.h"

using namespace rfk;

EnumAPI::EnumImpl::EnumImpl(char const* name, std::size_t id, ArchetypeAPI const* underlyingArchetype, EntityAPI const* outerEntity) noexcept:
	ArchetypeImpl(name, id, EEntityKind::Enum, underlyingArchetype->getMemorySize(), outerEntity),
	_underlyingArchetype{*underlyingArchetype}
{
}

EnumValueAPI& EnumAPI::EnumImpl::addEnumValue(char const* name, std::size_t id, int64 value, EnumAPI const*	backRef) noexcept
{
	return _enumValues.emplace_back(name, id, value, backRef);
}

void EnumAPI::EnumImpl::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	_enumValues.reserve(capacity);
}

std::vector<EnumValueAPI> const& EnumAPI::EnumImpl::getEnumValues() const noexcept
{
	return _enumValues;
}

ArchetypeAPI const& EnumAPI::EnumImpl::getUnderlyingArchetype() const noexcept
{
	return _underlyingArchetype;
}