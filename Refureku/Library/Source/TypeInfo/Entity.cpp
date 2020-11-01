#include "Refureku/TypeInfo/Entity.h"

#include <utility>

using namespace rfk;

Entity::Entity(std::string&& name, uint64 id, EEntityKind kind)	noexcept:
	name{std::forward<std::string>(name)},
	id{id},
	kind{kind}
{
}