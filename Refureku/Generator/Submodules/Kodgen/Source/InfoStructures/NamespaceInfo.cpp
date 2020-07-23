#include "InfoStructures/NamespaceInfo.h"

using namespace kodgen;

NamespaceInfo::NamespaceInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EntityInfo::EType::Namespace)
{

}