#include "Kodgen/InfoStructures/EnumInfo.h"

using namespace kodgen;

EnumInfo::EnumInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EType::Enum),
	type{clang_getCursorType(cursor)},
	underlyingType{clang_getEnumDeclIntegerType(cursor)}
{
}

void EnumInfo::refreshOuterEntity() noexcept
{
	for (EnumValueInfo& enumValue : enumValues)
	{
		enumValue.outerEntity = this;
	}
}