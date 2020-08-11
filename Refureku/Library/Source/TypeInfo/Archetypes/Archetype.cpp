#include "Refureku/TypeInfo/Archetypes/Archetype.h"

#include <cassert>

#include "Refureku/TypeInfo/Functions/StaticMethod.h"

using namespace rfk;

Archetype::Archetype(std::string&& newName, uint64 newId, EKind kind, uint64 newMemorySize) noexcept:
	Entity(std::forward<std::string>(newName), newId, kind),
	memorySize{newMemorySize}
{
}