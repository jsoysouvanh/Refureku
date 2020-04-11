#pragma once

#include "Misc/FundamentalTypes.h"

#include "InfoStructures/EntityInfo.h"

namespace kodgen
{
	class EnumValueInfo : public EntityInfo
	{
		public:
			int64 defaultValue = 0;

			EnumValueInfo()															= default;
			EnumValueInfo(CXCursor const& cursor)									noexcept;
			EnumValueInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept;
			EnumValueInfo(EnumValueInfo const&)										= default;
			EnumValueInfo(EnumValueInfo&&)											= default;
			~EnumValueInfo()														= default;
	};
}