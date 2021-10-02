#include "Refureku/TypeInfo/DatabaseAPI.h"

#include "Refureku/TypeInfo/DatabaseImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"
#include "Refureku/TypeInfo/Entity/EntityCastAPI.h"

using namespace rfk;

DatabaseAPI::DatabaseAPI() noexcept:
	_pimpl(new DatabaseImpl())
{
}

DatabaseAPI::~DatabaseAPI() noexcept = default;

DatabaseAPI& DatabaseAPI::getInstance() noexcept
{
	static DatabaseAPI database;
	
	return database;
}

EntityAPI const* DatabaseAPI::getEntityById(std::size_t id) const noexcept
{
	return EntityUtility::getEntityPtrById(_pimpl->getEntitiesById(), id);
}

NamespaceAPI const* DatabaseAPI::getNamespaceById(std::size_t id) const noexcept
{
	return entityCast<NamespaceAPI>(getEntityById(id));
}

DatabaseAPI const& rfk::getDatabaseAPI() noexcept
{
	return DatabaseAPI::getInstance();
}