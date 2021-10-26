/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/Misc/EnumMacros.h"

namespace rfk
{
	/** Flags describing a (member) function, i.e. a method. */
	enum class EMethodFlags : uint16
	{
		/** No flag. */
		Default			= 0,

		/** Access specifiers. */
		Public			= 1 << 0,
		Protected		= 1 << 1,
		Private			= 1 << 2,

		/** static qualifier. */
		Static			= 1 << 3,

		/** inline qualifier. */
		Inline			= 1 << 4,

		/** virtual qualifier. */
		Virtual			= 1 << 5,

		/** virtual = 0 qualifier. */
		PureVirtual		= 1 << 6,

		/** override qualifier. */
		Override		= 1 << 7,

		/** final qualifier. */
		Final			= 1 << 8,

		/** const qualifier. */
		Const			= 1 << 9
	};

	RFK_GENERATE_ENUM_OPERATORS(EMethodFlags)
}