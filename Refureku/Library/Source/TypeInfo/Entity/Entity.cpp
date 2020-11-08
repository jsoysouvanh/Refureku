#include "Refureku/TypeInfo/Entity/Entity.h"

#include <utility>		//std::forward
#include <algorithm>	//std::find

using namespace rfk;

Entity::Entity(std::string&& name, uint64 id, EEntityKind kind)	noexcept:
	name{std::forward<std::string>(name)},
	id{id},
	kind{kind}
{
}

bool Entity::addProperty(Property const* toAddProperty) noexcept
{
	if (!toAddProperty->getAllowMultiple())
	{
		//Check if a property of the same type is already in this entity,
		//in which case we abort the add
		if (std::find_if(properties.cbegin(), properties.cend(), [toAddProperty](Property const* ownedProperty) { return &toAddProperty->getArchetype() == &ownedProperty->getArchetype(); }) != properties.cend())
		{
			return false;
		}
	}

	properties.emplace_back(toAddProperty);

	return true;
}

void Entity::inheritProperties(Entity const& from) noexcept
{
	for (Property const* property : from.properties)
	{
		if (property->getShouldInherit())
		{
			addProperty(property);
		}
	}
}