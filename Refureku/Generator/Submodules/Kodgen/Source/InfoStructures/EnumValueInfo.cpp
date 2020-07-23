#include "InfoStructures/EnumValueInfo.h"

using namespace kodgen;

EnumValueInfo::EnumValueInfo(CXCursor const& cursor) noexcept:
	EntityInfo(cursor, PropertyGroup(), EType::EnumValue),
	defaultValue{clang_getEnumConstantDeclValue(cursor)}
{
}