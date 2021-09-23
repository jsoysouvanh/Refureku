#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

using namespace rfk;

FundamentalArchetype::FundamentalArchetype(std::string&& name, std::size_t id, std::size_t memorySize) noexcept:
	Archetype(std::forward<std::string>(name), id, EEntityKind::FundamentalArchetype, memorySize)
{
}