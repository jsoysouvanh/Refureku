#pragma once

#include "TypeInfo/Archetype.h"
#include "TypeInfo/Database.h"

namespace rfk
{
	class ArchetypeRegisterer
	{
		public:
			ArchetypeRegisterer()							= delete;
			ArchetypeRegisterer(Archetype const& archetype)	noexcept { Database::registerArchetype(archetype); }
			ArchetypeRegisterer(ArchetypeRegisterer const&)	= delete;
			ArchetypeRegisterer(ArchetypeRegisterer&&)		= delete;
			~ArchetypeRegisterer()							= default;

			ArchetypeRegisterer& operator=(ArchetypeRegisterer const&)	= delete;
			ArchetypeRegisterer& operator=(ArchetypeRegisterer&&)		= delete;
	};
}