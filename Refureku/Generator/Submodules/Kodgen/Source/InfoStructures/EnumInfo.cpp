#include "InfoStructures/EnumInfo.h"

using namespace kodgen;

EnumInfo::EnumInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EType::Enum)
{
}