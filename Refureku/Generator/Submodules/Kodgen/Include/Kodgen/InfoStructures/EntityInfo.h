/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <iostream>

#include <clang-c/Index.h>

#include "Kodgen/Misc/FundamentalTypes.h"
#include "Kodgen/InfoStructures/EEntityType.h"
#include "Kodgen/Properties/PropertyGroup.h"

namespace kodgen
{
	class EntityInfo
	{
		public:
			/** Type of entity. */
			EEntityType			entityType	= EEntityType::Undefined;
			
			/** Name of the entity. */
			std::string			name		= "";
			
			/** Unique id of the entity. */
			std::string			id			= "";
			
			/** Entity this entity is contained into, nullptr if none (file level). */
			EntityInfo const*	outerEntity	= nullptr;
			
			/** All properties bound to this entity. */
			PropertyGroup		properties;

			EntityInfo()								= default;
			EntityInfo(CXCursor const&	cursor,
					   PropertyGroup&&	propertyGroup,
					   EEntityType		entityType)		noexcept;
			EntityInfo(EntityInfo const&)				= default;
			EntityInfo(EntityInfo&&)					= default;
			~EntityInfo()								= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, EntityInfo const&) noexcept;
}