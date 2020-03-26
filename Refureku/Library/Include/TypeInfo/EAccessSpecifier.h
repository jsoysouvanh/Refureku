#pragma once

#include "Misc/FundamentalTypes.h"

namespace refureku
{
	enum class EAccessSpecifier : uint8
	{
		Undefined	= 0,

		Public		= 1,
		Protected	= 2,
		Private		= 3
	};
}