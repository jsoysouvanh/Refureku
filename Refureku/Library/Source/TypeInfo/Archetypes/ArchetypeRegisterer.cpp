#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegistererImpl.h"

using namespace rfk;

ArchetypeRegisterer::ArchetypeRegisterer(Archetype const& archetype) noexcept:
	_pimpl(new internal::ArchetypeRegistererImpl(archetype))
{
}

ArchetypeRegisterer::~ArchetypeRegisterer() noexcept = default;