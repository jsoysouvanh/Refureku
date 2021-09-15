#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"

#include "Refureku/TypeInfo/Database.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

using namespace rfk;

ArchetypeRegisterer::ArchetypeRegisterer(Archetype const& archetype) noexcept:
	_registeredArchetype{archetype}
{
	//Archetypes which are not at file level should not be registered
	assert(_registeredArchetype.outerEntity == nullptr);

	Database::getInternal().registerFileLevelEntity(_registeredArchetype, true);
}

ArchetypeRegisterer::~ArchetypeRegisterer() noexcept
{
	Database::getInternal().unregisterEntity(_registeredArchetype, true);
}