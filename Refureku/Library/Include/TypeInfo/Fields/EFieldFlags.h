#pragma once

#include "Misc/FundamentalTypes.h"
#include "Utility/EnumMacros.h"

namespace rfk
{
	enum class EFieldFlags : uint8
	{
		/** No flag */
		Default			= 0,

		/** Access specifiers */
		Public			= 1 << 0,
		Protected		= 1 << 1,
		Private			= 1 << 2,

		/** Method qualifiers */
		Static			= 1 << 3,
		Mutable			= 1 << 4
	};

	GENERATE_ENUM_OPERATORS(EFieldFlags)
}