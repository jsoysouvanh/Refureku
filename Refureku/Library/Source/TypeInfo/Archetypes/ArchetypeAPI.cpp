#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

ArchetypeAPI::ArchetypeAPI(ArchetypeImpl* implementation, void (*customDeleter)(EntityImpl*)) noexcept:
	EntityAPI(implementation, customDeleter)
{
}

ArchetypeAPI::ArchetypeAPI(char const* name, std::size_t id, EEntityKind kind, std::size_t memorySize, EntityAPI const* outerEntity) noexcept:
	EntityAPI(new ArchetypeImpl(name, id, kind, memorySize, outerEntity), [](EntityImpl* ptr) { delete reinterpret_cast<ArchetypeImpl*>(ptr); })
{
	//TODO: Delete this
}

ArchetypeAPI::ArchetypeAPI(ArchetypeAPI&&) noexcept = default;

ArchetypeAPI::~ArchetypeAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

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