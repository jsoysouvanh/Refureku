#include "TypeInfo/Class.h"

using namespace refureku;

Class::Class(std::string&& newName, uint64 newId, ECategory newCategory) noexcept:
	Struct(std::forward<std::string>(newName), std::forward<uint64>(newId), std::forward<ECategory>(newCategory))
{
}