#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

ArchetypeAPI::ArchetypeAPI(ArchetypeImpl* implementation) noexcept:
	EntityAPI(implementation)
{
}

ArchetypeAPI::ArchetypeAPI(ArchetypeAPI&&) noexcept = default;

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