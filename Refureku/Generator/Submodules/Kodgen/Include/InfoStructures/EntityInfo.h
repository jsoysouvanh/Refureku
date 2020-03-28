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

				/**
				*	Unset
				*/
				Count
			};

			EType			entityType	= EType::Count;
			std::string		name		= "";
			std::string		id			= "";
			PropertyGroup	properties;

			EntityInfo()																			= default;
			EntityInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup, EType&& entityType)	noexcept;
			EntityInfo(EntityInfo const&)															= default;
			EntityInfo(EntityInfo&&)																= default;
			~EntityInfo()																			= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, EntityInfo const&) noexcept;
}