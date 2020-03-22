#pragma once

#include <vector>

#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/EnumValueInfo.h"

namespace kodgen
{
	class EnumInfo : public EntityInfo
	{
		public:
			std::string					underlyingType			= "";
			std::string					canonicalUnderlyingType	= "";
			std::vector<EnumValueInfo>	enumValues;

			EnumInfo()															= default;
			EnumInfo(std::string&& entityName, PropertyGroup&& propertyGroup)	noexcept;
			EnumInfo(EnumInfo const&)											= default;
			EnumInfo(EnumInfo&&)												= default;
			~EnumInfo()															= default;
	};
}