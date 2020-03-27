#include "TypeInfo/Type.h"

using namespace refureku;

Type::Type(std::string&& newName, uint64 newId, ECategory newCategory) noexcept:
	name{std::forward<std::string>(newName)},
	id{newId},
	category{newCategory}
{
}