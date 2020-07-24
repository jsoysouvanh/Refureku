#include "InfoStructures/NamespaceInfo.h"

using namespace kodgen;

NamespaceInfo::NamespaceInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EntityInfo::EType::Namespace)
{
}

void NamespaceInfo::refreshOuterEntity() noexcept
{
	for (NamespaceInfo& namespaceInfo : namespaces)
	{
		namespaceInfo.refreshOuterEntity();
		namespaceInfo.outerEntity = this;
	}

	for (StructClassInfo& structInfo : structs)
	{
		structInfo.refreshOuterEntity();
		structInfo.outerEntity = this;
	}

	for (StructClassInfo& classInfo : classes)
	{
		classInfo.refreshOuterEntity();
		classInfo.outerEntity = this;
	}

	for (EnumInfo& enumInfo : enums)
	{
		enumInfo.refreshOuterEntity();
		enumInfo.outerEntity = this;
	}
}