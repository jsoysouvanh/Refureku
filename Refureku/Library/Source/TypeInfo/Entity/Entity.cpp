#include "Refureku/TypeInfo/Entity/Entity.h"

#include <utility>		//std::forward
#include <algorithm>	//std::find

#include "Refureku/TypeInfo/Archetypes/Struct.h"

using namespace rfk;

Entity::Entity(std::string&& name, std::size_t id, EEntityKind kind, Entity const* outerEntity) noexcept:
	_name{std::forward<std::string>(name)},
	_id{id},
	_kind{kind},
	_outerEntity{outerEntity}
{
}

Property const* Entity::getProperty(Struct const& archetype, bool isChildClassValid) const noexcept
{
	//Iterate over all props to find a matching property
	if (isChildClassValid)
	{
		for (Property const* p : _properties)
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
		for (Property const* p : _properties)
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
		for (Property const* p : _properties)
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
		for (Property const* p : _properties)
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
		if (std::find_if(_properties.cbegin(), _properties.cend(), [toAddProperty](Property const* ownedProperty) { return &toAddProperty->getArchetype() == &ownedProperty->getArchetype(); }) != _properties.cend())
		{
			return false;
		}
	}

	_properties.emplace_back(toAddProperty);

	return true;
}

void Entity::inheritProperties(Entity const& from) noexcept
{
	for (Property const* property : from._properties)
	{
		if (property->getShouldInherit())
		{
			addProperty(property);
		}
	}
}

void Entity::inheritAllProperties(Entity const& from) noexcept
{
	for (Property const* property : from._properties)
	{
		addProperty(property);
	}
}

std::string const& Entity::getName() const noexcept
{
	return _name;
}

std::size_t Entity::getId() const noexcept
{
	return _id;
}

EEntityKind Entity::getKind() const noexcept
{
	return _kind;
}

Entity const* Entity::getOuterEntity() const noexcept
{
	return _outerEntity;
}

void Entity::setOuterEntity(Entity const* outerEntity) noexcept
{
	_outerEntity = outerEntity;
}

std::vector<Property const*> const& Entity::getProperties() const noexcept
{
	return _properties;
}

std::vector<Property const*>& Entity::getProperties() noexcept
{
	return _properties;
}