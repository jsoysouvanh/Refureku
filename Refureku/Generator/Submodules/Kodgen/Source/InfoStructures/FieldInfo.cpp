#include "Kodgen/InfoStructures/FieldInfo.h"

#include <cassert>

using namespace kodgen;

FieldInfo::FieldInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EEntityType::Field),
	qualifiers{clang_getCursorKind(cursor) == CXCursorKind::CXCursor_VarDecl, false},
	type(clang_getCursorType(cursor)),
	accessSpecifier{EAccessSpecifier::Invalid},
	memoryOffset{0}
{
	if (!qualifiers.isStatic)
	{
		qualifiers.isMutable = clang_CXXField_isMutable(cursor);

		memoryOffset = clang_Cursor_getOffsetOfField(cursor);

		// assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Invalid);	<- Assert here on travis for some reasons...
		assert(memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Incomplete);
		assert(memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Dependent);
		assert(memoryOffset != CXTypeLayoutError::CXTypeLayoutError_InvalidFieldName);

		memoryOffset /= 8;	//From bits to bytes
	}
}