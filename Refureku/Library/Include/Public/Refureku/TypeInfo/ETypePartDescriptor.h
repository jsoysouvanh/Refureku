/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/Misc/EnumMacros.h"

namespace rfk
{
	enum class ETypePartDescriptor : uint16
	{
		/** Default uninitialized value for this enum */
		Undefined	= 0,

		/** Keywords */
		Const		= 1 << 0,
		//Restrict	= 1 << 1,
		Volatile	= 1 << 2,

		/** Ptr/Ref/Array */
		Ptr			= 1 << 3,
		LRef		= 1 << 4,
		RRef		= 1 << 5,
		CArray		= 1 << 6,
		Value		= 1 << 7	//Means non-ptr simple value, ex: int
	};

	RFK_GENERATE_ENUM_OPERATORS(ETypePartDescriptor)
}