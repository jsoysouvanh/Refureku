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
	enum class EFieldFlags : uint8
	{
		/** No flag */
		Default			= 0,

		/** Access specifiers */
		Public			= 1 << 0,
		Protected		= 1 << 1,
		Private			= 1 << 2,

		/** Field qualifiers */
		Static			= 1 << 3,
		Mutable			= 1 << 4
	};

	GENERATE_ENUM_OPERATORS(EFieldFlags)
}