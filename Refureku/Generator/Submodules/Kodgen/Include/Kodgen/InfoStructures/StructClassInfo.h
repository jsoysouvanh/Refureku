/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <memory>

#include <clang-c/Index.h>

#include "Kodgen/InfoStructures/EntityInfo.h"
#include "Kodgen/InfoStructures/EnumInfo.h"
#include "Kodgen/InfoStructures/FieldInfo.h"
#include "Kodgen/InfoStructures/MethodInfo.h"
#include "Kodgen/InfoStructures/NestedEnumInfo.h"
#include "Kodgen/Misc/EAccessSpecifier.h"

namespace kodgen
{
	//Forward declaration
	class NestedStructClassInfo;

	/**
	*	This class defines common data / behaviors shared by class and structs.
	*/
	class StructClassInfo : public EntityInfo
	{
		public:
			struct ParentInfo
			{
				/** Inheritance access of this parent. */
				EAccessSpecifier	inheritanceAccess;

				/** Type of the parent. */
				TypeInfo			type;
			};

			struct ClassQualifiers
			{
				/** Is the class final qualified of not. */
				bool isFinal		: 1;
			}													qualifiers;

			/** More detailed information on this class. */
			TypeInfo											type;

			/** List of all parent classes of this class. */
			std::vector<ParentInfo>								parents;

			/** List of all nested classes contained in this class. */
			std::vector<std::shared_ptr<NestedStructClassInfo>>	nestedClasses;

			/** List of all nested structs contained in this class. */
			std::vector<std::shared_ptr<NestedStructClassInfo>>	nestedStructs;

			/** List of all nested enums contained in this class. */
			std::vector<NestedEnumInfo>							nestedEnums;

			/** List of all fields contained in this class. */
			std::vector<FieldInfo>								fields;

			/** List of all methods contained in this class. */
			std::vector<MethodInfo>								methods;

			/** Does this class inherits from kodgen::Object. */
			bool												isObject;

			StructClassInfo()								noexcept;
			StructClassInfo(CXCursor const&	cursor,
							PropertyGroup&&	propertyGroup,
							EEntityType&&	entityType)		noexcept;
			StructClassInfo(StructClassInfo const&)			= default;
			StructClassInfo(StructClassInfo&&)				= default;
			~StructClassInfo()								= default;

			/**
			*	@brief Refresh the outerEntity field of all nested entities. Internal use only.
			*/
			void	refreshOuterEntity()	noexcept;
	};
}