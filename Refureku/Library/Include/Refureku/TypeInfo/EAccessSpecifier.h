/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Misc/FundamentalTypes.h"

namespace rfk
{
	enum class EAccessSpecifier : uint8
	{
		Undefined	= 0,

		Public		= 1,
		Protected	= 2,
		Private		= 3
	};
}