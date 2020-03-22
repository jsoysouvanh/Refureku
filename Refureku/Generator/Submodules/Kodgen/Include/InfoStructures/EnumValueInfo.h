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
			EnumValueInfo(std::string&& entityName, PropertyGroup&& propertyGroup)	noexcept;
			EnumValueInfo(EnumValueInfo const&)										= default;
			EnumValueInfo(EnumValueInfo&&)											= default;
			~EnumValueInfo()														= default;
	};
}