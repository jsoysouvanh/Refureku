/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Kodgen/InfoStructures/StructClassInfo.h"
#include "Kodgen/Misc/EAccessSpecifier.h"

namespace kodgen
{
	class NestedStructClassInfo : public StructClassInfo
	{
		public:
			/** Access specifier of this nested struct/class. */
			EAccessSpecifier	accessSpecifier;

			NestedStructClassInfo()										= default;
			NestedStructClassInfo(StructClassInfo&& base,
								  EAccessSpecifier	accessSpecifier)	noexcept;
			NestedStructClassInfo(NestedStructClassInfo const&)			= default;
			NestedStructClassInfo(NestedStructClassInfo&&)				= default;
			~NestedStructClassInfo()									= default;
	};
}