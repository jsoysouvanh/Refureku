#include "Refureku/TypeInfo/Archetypes/Archetype.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<Archetype const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<Archetype const*, rfk::Allocator<Archetype const*>>;

Archetype::Archetype(ArchetypeImpl* implementation) noexcept:
	Entity(implementation)
{
}

Archetype::~Archetype() noexcept = default;

EAccessSpecifier Archetype::getAccessSpecifier() const noexcept
{
	return getPimpl()->getAccessSpecifier();
}

void Archetype::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	getPimpl()->setAccessSpecifier(accessSpecifier);
}

std::size_t Archetype::getMemorySize() const noexcept
{
	return getPimpl()->getMemorySize();
}