#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	enum class EAccessSpecifier : uint8
	{
		Invalid		= 0,
		Public		= 1,
		Protected	= 2,
		Private		= 3
	};

	std::string toString(EAccessSpecifier error) noexcept;
}