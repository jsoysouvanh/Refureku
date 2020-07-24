#pragma once

#include <vector>

#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/EnumInfo.h"

namespace kodgen
{
	class NamespaceInfo : public EntityInfo
	{
		public:
			/** Nested namespaces. */
			std::vector<NamespaceInfo>		namespaces;

			/** Nested structs. */
			std::vector<StructClassInfo>	structs;

			/** Nested classes. */
			std::vector<StructClassInfo>	classes;

			/** Nested enums. */
			std::vector<EnumInfo>			enums;

			//TODO: Global functions
			//TODO: Global fields

			NamespaceInfo()															= default;
			NamespaceInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept;
			NamespaceInfo(NamespaceInfo const&)										= default;
			NamespaceInfo(NamespaceInfo&&)											= default;
			~NamespaceInfo()														= default;

			/**
			*	@brief Refresh the outerEntity field of all nested entities. Internal use only.
			*/
			void	refreshOuterEntity()	noexcept;
	};
}