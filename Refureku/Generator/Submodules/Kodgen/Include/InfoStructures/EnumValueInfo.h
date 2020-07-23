#pragma once

#include "Misc/FundamentalTypes.h"

#include "InfoStructures/EntityInfo.h"

namespace kodgen
{
	class EnumValueInfo : public EntityInfo
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