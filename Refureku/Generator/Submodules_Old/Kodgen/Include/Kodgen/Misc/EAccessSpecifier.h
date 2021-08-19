/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Kodgen/Misc/FundamentalTypes.h"

namespace kodgen
{
	enum class EAccessSpecifier : uint8
	{
		Invalid		= 0u,
		Public		= 1u,
		Protected	= 2u,
		Private		= 3u
	};

	std::string toString(EAccessSpecifier error) noexcept;
}