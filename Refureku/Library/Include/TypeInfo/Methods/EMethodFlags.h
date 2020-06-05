/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Misc/FundamentalTypes.h"
#include "Utility/EnumMacros.h"

namespace rfk
{
	enum class EMethodFlags : uint16
	{
		/** No flag */
		Default			= 0,

		/** Access specifiers */
		Public			= 1 << 0,
		Protected		= 1 << 1,
		Private			= 1 << 2,

		/** Method qualifiers */
		Static			= 1 << 3,
		Inline			= 1 << 4,
		Virtual			= 1 << 5,
		PureVirtual		= 1 << 6,
		Override		= 1 << 7,
		Final			= 1 << 8,
		Const			= 1 << 9
	};

	GENERATE_ENUM_OPERATORS(EMethodFlags)
}