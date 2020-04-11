#pragma once

#include "TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class ReflectedObject
	{
		public:
			virtual ~ReflectedObject() = default;

			virtual	Archetype const& getArchetype()	const noexcept = 0;
	};
}