#include "InfoStructures/EnumValueInfo.h"

using namespace kodgen;

EnumValueInfo::EnumValueInfo(CXCursor const& cursor) noexcept:
	EntityInfo(cursor, PropertyGroup(), EType::EnumValue)
{
	defaultValue = clang_getEnumConstantDeclValue(cursor);
}

EnumValueInfo::EnumValueInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EType::EnumValue)
{
	defaultValue = clang_getEnumConstantDeclValue(cursor);
}