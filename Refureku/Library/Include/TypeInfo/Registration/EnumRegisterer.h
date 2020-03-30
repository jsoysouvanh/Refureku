#pragma once

#include "TypeInfo/Database.h"

namespace rfk
{
	class EnumRegisterer
	{
		public:
			EnumRegisterer()							= delete;
			//TODO: EnumRegisterer(Enum const& enum)	noexcept { /** Database::registerEnum(archetype); */ }
			EnumRegisterer(EnumRegisterer const&)		= delete;
			EnumRegisterer(EnumRegisterer&&)			= delete;
			~EnumRegisterer()							= default;

			EnumRegisterer& operator=(EnumRegisterer const&)	= delete;
			EnumRegisterer& operator=(EnumRegisterer&&)			= delete;
	};
}