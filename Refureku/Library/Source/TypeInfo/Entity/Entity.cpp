#include "Refureku/TypeInfo/Entity/Entity.h"

#include <cstring>	//std::strcmp

#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/Misc/Algorithm.h"

using namespace rfk;

Entity::Entity(EntityImpl* implementation) noexcept:
	_pimpl{implementation}
{
}

Entity::Entity(Entity&&) noexcept = default;

Entity::~Entity() noexcept = default;

Property const* Entity::getPropertyAt(std::size_t propertyIndex) const noexcept
{
	return _pimpl->getProperties()[propertyIndex];
}

Property const* Entity::getProperty(Struct const& archetype, bool isChildClassValid) const noexcept
{
	//Iterate over all props to find a matching property
	if (isChildClassValid)
	{
		for (Property const* p : _pimpl->getProperties())
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
		for (Property const* p : _pimpl->getProperties())
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

Property const* Entity::getPropertyByName(char const* name) const noexcept
{
	return getPropertyByPredicate([](Property const& prop, void* userData)
								  {
									  return prop.getArchetype().hasSameName(*reinterpret_cast<char const**>(userData)); 
								  }, &name);
}

Property const* Entity::getPropertyByPredicate(Predicate<Property> predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getProperties(), predicate, userData);
}

Vector<Property const*> Entity::getProperties(Struct const& archetype, bool isChildClassValid) const noexcept
{
	Vector<Property const*> result;

	//Iterate over all props to find a matching property
	if (isChildClassValid)
	{
		for (Property const* p : _pimpl->getProperties())
		{
			//Consider child classes as valid
			if (archetype.isBaseOf(p->getArchetype()))
			{
				result.push_back(p);
			}
		}
	}
	else
	{
		for (Property const* p : _pimpl->getProperties())
		{
			//Child classes are not considered
			if (archetype == p->getArchetype())
			{
				result.push_back(p);
			}
		}
	}

	return result;
}

Vector<Property const*> Entity::getPropertiesByName(char const* name) const noexcept
{
	return getPropertiesByPredicate([](Property const& prop, void* userData)
									{
										return prop.getArchetype().hasSameName(*reinterpret_cast<char const**>(userData)); 
									}, &name);
}

Vector<Property const*> Entity::getPropertiesByPredicate(Predicate<Property> predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getProperties(), predicate, userData);
}

std::size_t Entity::getPropertiesCount() const noexcept
{
	return _pimpl->getProperties().size();
}

bool Entity::foreachProperty(Visitor<Property> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getProperties(), visitor, userData);
}

bool Entity::addProperty(Property const* property) noexcept
{
	return _pimpl->addProperty(property);
}

char const* Entity::getName() const noexcept
{
	return _pimpl->getName().data();
}

bool Entity::hasSameName(char const* name) const noexcept
{
	return name != nullptr && std::strcmp(getName(), name) == 0;
}

std::size_t Entity::getId() const noexcept
{
	return _pimpl->getId();
}

EEntityKind Entity::getKind() const noexcept
{
	return _pimpl->getKind();
}

Entity const* Entity::getOuterEntity() const noexcept
{
	return _pimpl->getOuterEntity();
}

void Entity::setOuterEntity(Entity const* outerEntity) noexcept
{
	_pimpl->setOuterEntity(outerEntity);
}

void Entity::setPropertiesCapacity(std::size_t capacity) noexcept
{
	_pimpl->setPropertiesCapacity(capacity);
}

bool Entity::operator==(Entity const& other) const noexcept
{
	return &other == this;
}

bool Entity::operator!=(Entity const& other) const noexcept
{
	return &other != this;
}