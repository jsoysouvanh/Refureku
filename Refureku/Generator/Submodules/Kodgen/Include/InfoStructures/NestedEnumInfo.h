/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/EnumInfo.h"
#include "Misc/EAccessSpecifier.h"

namespace kodgen
{
	class NestedEnumInfo : public EnumInfo
	{
		public:
			/** Access specifier of this nested struct/class. */
			EAccessSpecifier	accessSpecifier;

			NestedEnumInfo()									= default;
			NestedEnumInfo(EnumInfo&&		base,
						   EAccessSpecifier accessSpecifier)	noexcept;
			NestedEnumInfo(NestedEnumInfo const&)				= default;
			NestedEnumInfo(NestedEnumInfo&&)					= default;
			~NestedEnumInfo()									= default;
	};
}