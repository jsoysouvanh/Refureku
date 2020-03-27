#include "TypeInfo/Archetype.h"

using namespace refureku;

Archetype::Archetype(std::string&& newName, uint64 newId, ECategory newCategory) noexcept:
	name{std::forward<std::string>(newName)},
	id{newId},
	category{newCategory}
{
}