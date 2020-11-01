#include "Refureku/TypeInfo/Archetypes/Class.h"

using namespace rfk;

Class::Class(std::string&& name, uint64 id, uint64 memorySize) noexcept:
	Struct(std::forward<std::string>(name), id, EEntityKind::Class, memorySize)
{
}