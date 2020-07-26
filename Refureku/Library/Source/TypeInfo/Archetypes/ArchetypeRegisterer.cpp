#include "TypeInfo/Archetypes/ArchetypeRegisterer.h"

#include "TypeInfo/Database.h"

using namespace rfk;

ArchetypeRegisterer::ArchetypeRegisterer(Archetype const* archetype) noexcept
{
	Database::registerFileLevelEntity(*archetype);
}