#include "Refureku/TypeInfo/Entity/Entity.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Entity/EntityImpl.h"

//#include "Refureku/TypeInfo/Archetypes/StructAPI.h"

using namespace rfk;

EntityAPI::EntityAPI() noexcept:
	_pimpl{static_cast<EntityImpl*>(nullptr)}
{
}

EntityAPI::EntityAPI(char const* name, std::size_t id, EEntityKind kind, EntityAPI const* outerEntity) noexcept:
	_pimpl(name, id, kind, outerEntity)
{
}

EntityAPI::EntityAPI(EntityAPI const& other) noexcept:
	_pimpl{other._pimpl}
{
}

EntityAPI::EntityAPI(EntityAPI&& other) noexcept:
	_pimpl{std::forward<Pimpl<EntityImpl>>(other._pimpl)}
{
}

EntityAPI::~EntityAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

void EntityAPI::setImpl(EntityImpl* implementation) noexcept
{
	_pimpl.set(implementation);
}

Property const* EntityAPI::getPropertyAt(std::size_t propertyIndex) const noexcept
{
	return _pimpl->getProperties()[propertyIndex];
}

Property const* EntityAPI::getProperty(StructAPI const& archetype, bool isChildClassValid) const noexcept
{
	//TODO

	return nullptr;
}

Property const* EntityAPI::getProperty(PropertyPredicate predicate, void* userData) const noexcept
{
	for (Property const* prop : _pimpl->getProperties())
	{
		if (predicate(*prop, userData))
		{
			return prop;
		}
	}
	
	return nullptr;
}

Vector<Property const*> EntityAPI::getProperties(StructAPI const& archetype, bool isChildClassValid) const noexcept
{
	Vector<Property const*> result;

	std::vector<Property const*> properties;

	//TODO
	//Iterate over all props to find a matching property
	//if (isChildClassValid)
	//{
	//	for (Property const* p : properties)
	//	{
	//		//Consider child classes as valid
	//		if (archetype.isBaseOf(p->getArchetype()))
	//		{
	//			result.emplace_back(p);
	//		}
	//	}
	//}
	//else
	//{
	//	for (Property const* p : properties)
	//	{
	//		//Child classes are not considered
	//		if (archetype == p->getArchetype())
	//		{
	//			result.emplace_back(p);
	//		}
	//	}
	//}

	return result;
}

Vector<Property const*> EntityAPI::getProperties(PropertyPredicate	predicate, void* userData) const noexcept
{
	Vector<Property const*> result;

	for (Property const* prop : _pimpl->getProperties())
	{
		if (predicate(*prop, userData))
		{
			result.push_back(prop);
		}
	}

	return result;
}

std::size_t EntityAPI::getPropertyCount() const noexcept
{
	return _pimpl->getProperties().size();
}

bool EntityAPI::addProperty(Property const* property) noexcept
{
	return _pimpl->addProperty(property);
}

void EntityAPI::inheritProperties(EntityAPI const& from) noexcept
{
	_pimpl->inheritProperties(*from._pimpl);
}

void EntityAPI::inheritAllProperties(EntityAPI const& from) noexcept
{
	_pimpl->inheritAllProperties(*from._pimpl);
}

char const* EntityAPI::getName() const noexcept
{
	return _pimpl->getName().data();
}

std::size_t EntityAPI::getId() const noexcept
{
	return _pimpl->getId();
}

EEntityKind EntityAPI::getKind() const noexcept
{
	return _pimpl->getKind();
}

EntityAPI const* EntityAPI::getOuterEntity() const noexcept
{
	return _pimpl->getOuterEntity();
}

void EntityAPI::setOuterEntity(EntityAPI const* outerEntity) noexcept
{
	_pimpl->setOuterEntity(outerEntity);
}

void EntityAPI::setPropertiesCapacity(std::size_t capacity) noexcept
{
	_pimpl->setPropertiesCapacity(capacity);
}

bool EntityAPI::operator==(EntityAPI const& other) const noexcept
{
	return &other == this;
}

bool EntityAPI::operator!=(EntityAPI const& other) const noexcept
{
	return &other != this;
}