#include "Kodgen/InfoStructures/MethodInfo.h"

#include <algorithm>
#include <cassert>

#include "Kodgen/Misc/Helpers.h"

using namespace kodgen;

MethodInfo::MethodInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	FunctionInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EEntityType::Method),
	isDefault{clang_CXXMethod_isDefaulted(cursor) != 0u},
	isVirtual{clang_CXXMethod_isVirtual(cursor) != 0u},
	isPureVirtual{clang_CXXMethod_isPureVirtual(cursor) != 0u},
	isOverride{false},
	isFinal{false},
	isConst{clang_CXXMethod_isConst(cursor) != 0u}
{
	assert(cursor.kind == CXCursorKind::CXCursor_CXXMethod);

	isStatic = clang_CXXMethod_isStatic(cursor) != 0u;
}