#include "InfoStructures/StructClassInfo.h"

#include "InfoStructures/NestedStructClassInfo.h"

using namespace kodgen;

StructClassInfo::StructClassInfo() noexcept:
	EntityInfo(),
	qualifiers{ false }
{
}

StructClassInfo::StructClassInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup, EType&& entityType) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), std::forward<EType>(entityType)),
	qualifiers{false},
	type{clang_getCursorType(cursor)}
{
}

void StructClassInfo::refreshOuterEntity() noexcept
{
	for (std::shared_ptr<NestedStructClassInfo>& nestedClass : nestedClasses)
	{
		nestedClass->refreshOuterEntity();
		nestedClass->outerEntity = this;
	}

	for (std::shared_ptr<NestedStructClassInfo>& nestedStruct : nestedStructs)
	{
		nestedStruct->refreshOuterEntity();
		nestedStruct->outerEntity = this;
	}

	for (NestedEnumInfo& nestedEnum : nestedEnums)
	{
		nestedEnum.refreshOuterEntity();
		nestedEnum.outerEntity = this;
	}

	for (FieldInfo& field : fields)
	{
		field.outerEntity = this;
	}

	for (MethodInfo& method : methods)
	{
		method.outerEntity = this;
	}
}