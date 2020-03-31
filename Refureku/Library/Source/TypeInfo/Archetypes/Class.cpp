#include "TypeInfo/Archetypes/Class.h"

using namespace rfk;

Class::Class(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize) noexcept:
	Struct(std::forward<std::string>(newName), newId, newCategory, newMemorySize)
{
}