#include "TypeInfo/Entity.h"

#include <utility>

using namespace rfk;

Entity::Entity(std::string&& newName, uint64 newId, EKind kind)	noexcept:
	name{std::forward<std::string>(newName)},
	id{newId},
	kind{kind}
{
}