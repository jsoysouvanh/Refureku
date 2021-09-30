#include "Refureku/TypeInfo/Entity/EntityHash.h"

#include <string_view>
#include <cstring>		//std::strcmp

#include "Refureku/TypeInfo/Entity/Entity.h"

using namespace rfk;

std::size_t EntityNameHash::operator()(EntityAPI const& entity) const
{
	return std::hash<std::string_view>()(entity.getName());
}

std::size_t EntityIdHash::operator()(EntityAPI const& entity) const
{
	return entity.getId();
}

bool EntityNameEqual::operator()(EntityAPI const& lhs, EntityAPI const& rhs) const
{
	return std::strcmp(lhs.getName(), rhs.getName()) == 0;
}

bool EntityIdEqual::operator()(EntityAPI const& lhs, EntityAPI const& rhs) const
{
	return lhs.getId() == rhs.getId();
}

std::size_t EntityPtrNameHash::operator()(EntityAPI const* entity) const
{
	return std::hash<std::string_view>()(entity->getName());
}

std::size_t EntityPtrIdHash::operator()(EntityAPI const* entity) const
{
	return entity->getId();
}

bool EntityPtrNameEqual::operator()(EntityAPI const* lhs, EntityAPI const* rhs)	const
{
	return std::strcmp(lhs->getName(), rhs->getName()) == 0;
}

bool EntityPtrIdEqual::operator()(EntityAPI const* lhs, EntityAPI const* rhs) const
{
	return lhs->getId() == rhs->getId();
}