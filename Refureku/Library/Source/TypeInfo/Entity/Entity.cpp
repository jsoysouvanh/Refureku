#include "Refureku/TypeInfo/Entity/Entity.h"

#include <utility>		//std::forward
#include <algorithm>	//std::find

#include "Refureku/TypeInfo/Archetypes/Struct.h"

using namespace rfk;

Entity::Entity(std::string&& name, uint64 id, EEntityKind kind)	noexcept:
	name{std::forward<std::string>(name)},
	id{id},
	kind{kind}
{
}

Property const* Entity::getProperty(Struct const& archetype, bool isChildClassValid) const noexcept
{
	//Iterate over all props to find a matching property
	if (isChildClassValid)
	{
		for (Property const* p : properties)
		{
			//Consider child classes as valid
			if (archetype.isBaseOf(p->getArchetype()))
			{
				return p;
			}
		}
	}
	else
	{
		for (Property const* p : properties)
		{
			//Child classes are not considered
			if (archetype == p->getArchetype())
			{
				return p;
			}
		}
	}

	return nullptr;
}

std::vector<Property const*> Entity::getProperties(Struct const& archetype, bool isChildClassValid) const noexcept
{
	std::vector<Property const*> result;

	//Iterate over all props to find a matching property
	if (isChildClassValid)
	{
		for (Property const* p : properties)
		{
			//Consider child classes as valid
			if (archetype.isBaseOf(p->getArchetype()))
			{
				result.emplace_back(p);
			}
		}
	}
	else
	{
		for (Property const* p : properties)
		{
			//Child classes are not considered
			if (archetype == p->getArchetype())
			{
				result.emplace_back(p);
			}
		}
	}

	return result;
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