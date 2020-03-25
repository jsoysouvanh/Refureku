#pragma once

#include "Misc/FundamentalTypes.h"

namespace refureku
{
	enum class EAccessSpecifier : uint8
	{
		Undefined = 0,

		Public,
		Protected,
		Private
	};
}