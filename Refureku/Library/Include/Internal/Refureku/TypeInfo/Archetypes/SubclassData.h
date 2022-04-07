/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef> //std::ptrdiff_t

namespace rfk
{
	struct SubclassData
	{
		/** Bytes offset to add to a subclass instance to get a pointer to the base type. */
		std::ptrdiff_t	pointerOffset;

		SubclassData(std::ptrdiff_t pointerOffset) noexcept:
			pointerOffset{pointerOffset}
		{
		}
	};
}