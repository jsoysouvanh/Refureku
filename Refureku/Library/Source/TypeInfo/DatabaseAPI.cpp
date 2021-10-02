#include "Refureku/TypeInfo/DatabaseAPI.h"

#include "Refureku/TypeInfo/DatabaseImpl.h"

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

DatabaseAPI const& rfk::getDatabaseAPI() noexcept
{
	return DatabaseAPI::getInstance();
}