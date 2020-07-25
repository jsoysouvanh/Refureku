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

#include "Misc/FundamentalTypes.h"
#include "Properties/PropertyGroup.h"

namespace kodgen
{
	class EntityInfo
	{
		public:
			/**
			*	Enum representing type of an entity
			*	This avoids unnecessary dynamic casts and allows EntityInfo to be a non-polymorphic class
			*/
			enum class EType : uint8
			{
				Class,
				Struct,
				Enum,
				Field,
				Method,
				EnumValue,
				Namespace,

				/**
				*	Unset
				*/
				Count
			};

			/** Type of entity. */
			EType				entityType	= EType::Count;
			
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
					   EType			entityType)		noexcept;
			EntityInfo(EntityInfo const&)				= default;
			EntityInfo(EntityInfo&&)					= default;
			~EntityInfo()								= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, EntityInfo const&) noexcept;
}