#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"

#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

ArchetypeRegisterer::ArchetypeRegisterer(Archetype const* archetype) noexcept
{
	Database::registerFileLevelEntity(*archetype, true);
}