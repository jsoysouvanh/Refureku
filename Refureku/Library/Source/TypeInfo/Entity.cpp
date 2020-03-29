#include "TypeInfo/Entity.h"

#include <utility>

using namespace rfk;

Entity::Entity(std::string&& newName, uint64 newId)	noexcept:
	name{std::forward<std::string>(newName)},
	id{std::forward<uint64>(newId)}
{
}