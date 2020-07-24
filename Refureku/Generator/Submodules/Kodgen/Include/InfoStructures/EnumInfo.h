#pragma once

#include <vector>

#include "InfoStructures/TypeInfo.h"
#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/EnumValueInfo.h"

namespace kodgen
{
	class EnumInfo : public EntityInfo
	{
		public:
			TypeInfo					type;
			TypeInfo					underlyingType;
			std::vector<EnumValueInfo>	enumValues;

			EnumInfo()														= default;
			EnumInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept;
			EnumInfo(EnumInfo const&)										= default;
			EnumInfo(EnumInfo&&)											= default;
			~EnumInfo()														= default;

			/**
			*	@brief Refresh the outerEntity field of all nested entities. Internal use only.
			*/
			void	refreshOuterEntity()	noexcept;
	};
}