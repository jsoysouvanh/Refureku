#pragma once

#include <vector>
#include <memory>
#include <clang-c/Index.h>

#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/EnumInfo.h"
#include "InfoStructures/FieldInfo.h"
#include "InfoStructures/MethodInfo.h"
#include "InfoStructures/NestedEnumInfo.h"
#include "Misc/EAccessSpecifier.h"

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

			StructClassInfo()																			noexcept;
			StructClassInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup, EType&& entityType)	noexcept;
			StructClassInfo(StructClassInfo const&)														= default;
			StructClassInfo(StructClassInfo&&)															= default;
			~StructClassInfo()																			= default;

			/**
			*	@brief Refresh the outerEntity field of all nested entities. Internal use only.
			*/
			void	refreshOuterEntity()	noexcept;
	};

	std::ostream& operator<<(std::ostream& out_stream, kodgen::StructClassInfo const&) noexcept;
}