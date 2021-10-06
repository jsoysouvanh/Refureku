/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline Entity::EntityImpl::EntityImpl(char const* name, std::size_t id, EEntityKind kind, Entity const* outerEntity) noexcept:
	_name{name},
	_properties{},
	_id{id},
	_outerEntity{outerEntity},
	_kind{kind}
{
}

inline bool Entity::EntityImpl::addProperty(Property const* toAddProperty) noexcept
{
	if (!toAddProperty->getAllowMultiple())
	{
		//Check if a property of the same type is already in this entity,
		//in which case we abort the add
		for (Property const* property : _properties)
		{
			if (&toAddProperty->getArchetype() == &property->getArchetype())
			{
				return false;
			}
		}
	}

	_properties.push_back(toAddProperty);

	return true;
}

inline void Entity::EntityImpl::inheritProperties(EntityImpl const& from) noexcept
{
	for (Property const* property : from._properties)
	{
		if (property->getShouldInherit())
		{
			addProperty(property);
		}
	}
}

inline void Entity::EntityImpl::inheritAllProperties(EntityImpl const& from) noexcept
{
	for (Property const* property : from._properties)
	{
		addProperty(property);
	}
}

inline std::string const& Entity::EntityImpl::getName() const noexcept
{
	return _name;
}

inline std::size_t Entity::EntityImpl::getId() const noexcept
{
	return _id;
}

inline EEntityKind Entity::EntityImpl::getKind() const noexcept
{
	return _kind;
}

inline Entity const* Entity::EntityImpl::getOuterEntity() const noexcept
{
	return _outerEntity;
}

inline std::vector<Property const*> const& Entity::EntityImpl::getProperties() const noexcept
{
	return _properties;
}

inline void Entity::EntityImpl::setOuterEntity(Entity const* outerEntity) noexcept
{
	_outerEntity = outerEntity;
}

inline void Entity::EntityImpl::setPropertiesCapacity(std::size_t capacity) noexcept
{
	_properties.reserve(capacity);
}