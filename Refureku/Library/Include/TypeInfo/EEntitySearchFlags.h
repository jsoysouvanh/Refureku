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
	enum class EEntitySearchFlags : uint8
	{
		/** No flag. */
		Default		= 0,

		/**
		*	Access specifiers.
		*	These flags are only relevant when looking for an entity nested inside
		*	a struct or a class.
		*/
		Public		= 1 << 0,
		Protected	= 1 << 1,
		Private		= 1 << 2,

		/** Search scope flags. */
		/** Allow searching for entities nested inside namespaces. */
		NamespaceNested	= 1 << 3,

		/** Allow searching for entities nested inside structs. */
		StructNested	= 1 << 4,

		/** Allow searching for entities nested inside classes. */
		ClassNested		= 1 << 5
	};

	GENERATE_ENUM_OPERATORS(EEntitySearchFlags)
}