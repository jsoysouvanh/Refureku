#pragma once

#include "TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	struct Type
	{
		public:
			Archetype const* archetype = nullptr;

			/** TODO: ptrDepth, isPointer(), isReference..., isArray */

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= default;
			~Type()				= default;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};
}