#include "Kodgen/InfoStructures/EnumValueInfo.h"

using namespace kodgen;

EnumValueInfo::EnumValueInfo(CXCursor const& cursor) noexcept:
	EntityInfo(cursor, PropertyGroup(), EEntityType::EnumValue),
	defaultValue{clang_getEnumConstantDeclValue(cursor)}
{
}