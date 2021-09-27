#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

ArchetypeAPI::ArchetypeImpl::ArchetypeImpl(char const* name, std::size_t id, EEntityKind kind, std::size_t memorySize, EntityAPI const* outerEntity) noexcept:
	EntityAPI::EntityImpl(name, id, kind, outerEntity),
	_memorySize{memorySize}
{
}

EAccessSpecifier ArchetypeAPI::ArchetypeImpl::getAccessSpecifier() const noexcept
{
	return _accessSpecifier;
}

void ArchetypeAPI::ArchetypeImpl::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	_accessSpecifier = accessSpecifier;
}

std::size_t ArchetypeAPI::ArchetypeImpl::getMemorySize() const noexcept
{
	return _memorySize;
}