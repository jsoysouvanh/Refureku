#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"

#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

ArchetypeRegisterer::ArchetypeRegisterer(Archetype const* archetype) noexcept:
	_registeredArchetype{archetype}
{
	//Archetypes which are not at file level should not be registered
	assert(_registeredArchetype->outerEntity == nullptr);

	Database::registerFileLevelEntity(*_registeredArchetype, true);
}

ArchetypeRegisterer::~ArchetypeRegisterer() noexcept
{
	//The registerer might have been default constructed, in which case _registeredArchetype
	//is nullptr, so we must check
	if (_registeredArchetype != nullptr)
	{
		Database::unregisterEntity(*_registeredArchetype, true);
	}
}