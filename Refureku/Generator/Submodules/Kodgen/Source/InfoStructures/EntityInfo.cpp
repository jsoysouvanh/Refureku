#include "InfoStructures/EntityInfo.h"

#include "Misc/Helpers.h"

using namespace kodgen;

EntityInfo::EntityInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup, EType entityType) noexcept:
	entityType{entityType},
	name{Helpers::getString(clang_getCursorDisplayName(cursor))},
	id{Helpers::getString(clang_getCursorUSR(cursor))},
	properties{std::forward<PropertyGroup>(propertyGroup)}
{
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, EntityInfo const& entityInfo) noexcept
{
	out_stream << entityInfo.name;

	return out_stream;
}