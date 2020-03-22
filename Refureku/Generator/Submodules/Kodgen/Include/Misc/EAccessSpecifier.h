#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	enum class EAccessSpecifier : uint8
	{
		Invalid		= 1 << 0,
		Public		= 1 << 1,
		Protected	= 1 << 2,
		Private		= 1 << 3
	};

	std::string toString(EAccessSpecifier error) noexcept;
}