#pragma once

#include <vector>

#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/EnumInfo.h"

namespace kodgen
{
	class NamespaceInfo : public EntityInfo
	{
		public:
			/**
			*	Nested namespaces, classes, structs and enums
			*/
			std::vector<NamespaceInfo>		namespaces;
			std::vector<StructClassInfo>	classes;
			std::vector<StructClassInfo>	structs;
			std::vector<EnumInfo>			enums;

			//TODO: Global functions
			//TODO: Global fields

			NamespaceInfo()															= default;
			NamespaceInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept;
			NamespaceInfo(NamespaceInfo const&)										= default;
			NamespaceInfo(NamespaceInfo&&)											= default;
			~NamespaceInfo()														= default;
	};
}