/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/EntityInfo.h"
#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	class EnumValueInfo final : public EntityInfo
	{
		public:
			/** Default integer value for this enum value. */
			int64 defaultValue = 0;

			EnumValueInfo()							= default;
			EnumValueInfo(CXCursor const& cursor)	noexcept;
			EnumValueInfo(EnumValueInfo const&)		= default;
			EnumValueInfo(EnumValueInfo&&)			= default;
			~EnumValueInfo()						= default;
	};
}