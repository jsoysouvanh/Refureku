#pragma once

#include "TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	class ReflectedObject
	{
		public:
		ReflectedObject()						= default;
		ReflectedObject(ReflectedObject const&) = default;
		ReflectedObject(ReflectedObject&&)		= default;
		virtual ~ReflectedObject()				= default;

		virtual	Struct const& getArchetype()	const noexcept = 0;
	};
}