#pragma once

#include "TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class ReflectedObject
	{
		public:
			virtual	Archetype const& getArchetype()	const noexcept = 0;
	};
}