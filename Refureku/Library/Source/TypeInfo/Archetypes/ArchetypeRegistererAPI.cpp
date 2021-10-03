#include "Refureku/TypeInfo/Archetypes/ArchetypeRegistererAPI.h"

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegistererImpl.h"

using namespace rfk;

ArchetypeRegistererAPI::ArchetypeRegistererAPI(ArchetypeAPI const& archetype) noexcept:
	_pimpl(new internal::ArchetypeRegistererImpl(archetype))
{
}

ArchetypeRegistererAPI::~ArchetypeRegistererAPI() noexcept = default;