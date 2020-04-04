#include "TypeInfo/Archetypes/Enum.h"

using namespace rfk;

Enum::Enum(std::string&& name, uint64 id, uint64 memorySize) noexcept:
	Archetype(std::forward<std::string>(name), id, ECategory::Enum, memorySize)
{
}