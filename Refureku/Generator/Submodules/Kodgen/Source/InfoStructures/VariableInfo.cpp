#include "Kodgen/InfoStructures/VariableInfo.h"

#include <cassert>

using namespace kodgen;

VariableInfo::VariableInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup, EEntityType entityType) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), entityType),
	isStatic{false},
	type(clang_getCursorType(cursor))
{
}

VariableInfo::VariableInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	VariableInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EEntityType::Variable)
{
	assert(cursor.kind == CXCursorKind::CXCursor_VarDecl);

	isStatic = clang_getCursorLinkage(cursor) == CXLinkage_Internal;
}