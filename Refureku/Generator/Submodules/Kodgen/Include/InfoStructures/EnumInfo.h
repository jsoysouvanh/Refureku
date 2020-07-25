/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include <clang-c/Index.h>

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

			EnumInfo()								= default;
			EnumInfo(CXCursor const& cursor,
					 PropertyGroup&& propertyGroup)	noexcept;
			EnumInfo(EnumInfo const&)				= default;
			EnumInfo(EnumInfo&&)					= default;
			~EnumInfo()								= default;

			/**
			*	@brief Refresh the outerEntity field of all nested entities. Internal use only.
			*/
			void	refreshOuterEntity()	noexcept;
	};
}