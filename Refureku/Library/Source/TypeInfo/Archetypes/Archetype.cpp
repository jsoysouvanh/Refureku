#include "Refureku/TypeInfo/Archetypes/Archetype.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

Archetype::Archetype(ArchetypeImpl* implementation) noexcept:
	Entity(implementation)
{
}

Archetype::Archetype(Archetype&&) noexcept = default;

Archetype::~Archetype() noexcept = default;

EAccessSpecifier Archetype::getAccessSpecifier() const noexcept
{
	return reinterpret_cast<ArchetypeImpl const*>(getPimpl())->getAccessSpecifier();
}

void Archetype::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	reinterpret_cast<ArchetypeImpl*>(getPimpl())->setAccessSpecifier(accessSpecifier);
}

std::size_t Archetype::getMemorySize() const noexcept
{
	return reinterpret_cast<ArchetypeImpl const*>(getPimpl())->getMemorySize();
}