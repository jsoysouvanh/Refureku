#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

using namespace rfk;

FundamentalArchetype::FundamentalArchetype(std::string&& name, uint64 id, uint64 memorySize) noexcept:
	Archetype(std::forward<std::string>(name), id, EKind::FundamentalArchetype, memorySize)
{
}