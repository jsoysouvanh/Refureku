#include "Refureku/TypeInfo/Entity/EntityHash.h"

#include <string_view>
#include <cstring>		//std::strcmp

#include "Refureku/TypeInfo/Entity/Entity.h"

using namespace rfk;

std::size_t EntityNameHash::operator()(Entity const& entity) const
{
	return std::hash<std::string_view>()(entity.getName());
}

std::size_t EntityIdHash::operator()(Entity const& entity) const
{
	return entity.getId();
}

bool EntityNameEqual::operator()(Entity const& lhs, Entity const& rhs) const
{
	return std::strcmp(lhs.getName(), rhs.getName()) == 0;
}

bool EntityIdEqual::operator()(Entity const& lhs, Entity const& rhs) const
{
	return lhs.getId() == rhs.getId();
}

std::size_t EntityPtrNameHash::operator()(Entity const* entity) const
{
	return std::hash<std::string_view>()(entity->getName());
}

std::size_t EntityPtrIdHash::operator()(Entity const* entity) const
{
	return entity->getId();
}

bool EntityPtrNameEqual::operator()(Entity const* lhs, Entity const* rhs)	const
{
	return std::strcmp(lhs->getName(), rhs->getName()) == 0;
}

bool EntityPtrIdEqual::operator()(Entity const* lhs, Entity const* rhs) const
{
	return lhs->getId() == rhs->getId();
}