#include "TypeInfo/Archetypes/Archetype.h"

#include <cassert>

#include "TypeInfo/Methods/StaticMethod.h"

using namespace rfk;

Archetype::Archetype(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize) noexcept:
	Entity(std::forward<std::string>(newName), newId, EKind::Archetype),
	category{newCategory},
	memorySize{newMemorySize}
{
}