/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/Utility/EnumMacros.h"

namespace rfk
{
	/** Flags describing a (non-member) function. */
	enum class EFunctionFlags : uint8
	{
		/** No flag. */
		Default			= 0,

		/** static qualifier. */
		Static			= 1 << 0,

		/** inline qualifier. */
		Inline			= 1 << 1
	};

	GENERATE_ENUM_OPERATORS(EFunctionFlags)
}