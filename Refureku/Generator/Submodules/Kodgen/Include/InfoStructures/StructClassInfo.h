#pragma once

#include <vector>
#include <unordered_map>
#include <clang-c/Index.h>

#include "InfoStructures/EntityInfo.h"
#include "Misc/EAccessSpecifier.h"
#include "InfoStructures/FieldInfo.h"
#include "InfoStructures/MethodInfo.h"

namespace kodgen
{
	/**
	*	This class defines common data / behaviors shared by class and structs
	*/
	class StructClassInfo : public EntityInfo
	{
		public:
			struct ParentInfo
			{
				EAccessSpecifier	inheritanceAccess;
				TypeInfo			type;
			};

			struct ClassQualifiers
			{
				bool isFinal		: 1;
			}								qualifiers;

			std::string						nameSpace;
			std::vector<ParentInfo>			parents;
			std::vector<FieldInfo>			fields;
			std::vector<MethodInfo>			methods;

			StructClassInfo()																			noexcept;
			StructClassInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup, EType&& entityType)	noexcept;
			StructClassInfo(StructClassInfo const&)														= default;
			StructClassInfo(StructClassInfo&&)															= default;
			~StructClassInfo()																			= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, kodgen::StructClassInfo const&) noexcept;
}