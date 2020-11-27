#include "Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h"

#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

DefaultEntityRegisterer::DefaultEntityRegisterer(Entity const* entity) noexcept:
	_registeredEntity{entity}
{
	//Entities which are not at file level should not be registered
	assert(_registeredEntity->outerEntity == nullptr);

	//Register to database
	Database::registerFileLevelEntity(*entity, false);
}

DefaultEntityRegisterer::~DefaultEntityRegisterer()noexcept
{
	//Unregister from database
	Database::unregisterEntity(*_registeredEntity, false);
}
