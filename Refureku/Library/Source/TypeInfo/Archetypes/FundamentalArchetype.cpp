#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeImpl.h"

using namespace rfk;

FundamentalArchetype::FundamentalArchetype(char const* name, std::size_t id, std::size_t memorySize) noexcept:
	Archetype(new FundamentalArchetypeImpl(name, id, memorySize))
{
}

FundamentalArchetype::~FundamentalArchetype() noexcept = default;