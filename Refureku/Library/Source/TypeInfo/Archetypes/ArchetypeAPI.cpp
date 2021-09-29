#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

ArchetypeAPI::ArchetypeAPI(ArchetypeImpl* implementation) noexcept:
	EntityAPI(implementation)
{
}

ArchetypeAPI::ArchetypeAPI(char const* name, std::size_t id, EEntityKind kind, std::size_t memorySize, EntityAPI const* outerEntity) noexcept:
	EntityAPI(new ArchetypeImpl(name, id, kind, memorySize, outerEntity))
{
	//TODO: Delete this
}

ArchetypeAPI::~ArchetypeAPI() noexcept = default;

EAccessSpecifier ArchetypeAPI::getAccessSpecifier() const noexcept
{
	return reinterpret_cast<ArchetypeImpl const*>(getPimpl())->getAccessSpecifier();
}

void ArchetypeAPI::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	reinterpret_cast<ArchetypeImpl*>(getPimpl())->setAccessSpecifier(accessSpecifier);
}

std::size_t ArchetypeAPI::getMemorySize() const noexcept
{
	return reinterpret_cast<ArchetypeImpl const*>(getPimpl())->getMemorySize();
}