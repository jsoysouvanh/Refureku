#pragma once

#include "TypeInfo/Archetype.h"

namespace refureku
{
	struct Type
	{
		public:
			Archetype const* archetype = nullptr;

			/** TODO: ptrDepth, isPointer(), isReference... */

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= default;
			~Type()				= default;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};
}