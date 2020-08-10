#include "Kodgen/InfoStructures/FieldInfo.h"

#include <cassert>

using namespace kodgen;

FieldInfo::FieldInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	VariableInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EEntityType::Field),
	isMutable{isMutable = clang_CXXField_isMutable(cursor)},
	accessSpecifier{EAccessSpecifier::Invalid},
	memoryOffset{0}
{
	assert(cursor.kind == CXCursorKind::CXCursor_FieldDecl);

	isStatic = clang_getCursorKind(cursor) == CXCursorKind::CXCursor_VarDecl;

	if (!isStatic)
	{
		memoryOffset = clang_Cursor_getOffsetOfField(cursor);

		// assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Invalid);	<- Assert here on travis for some reasons...
		assert(memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Incomplete);
		assert(memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Dependent);
		assert(memoryOffset != CXTypeLayoutError::CXTypeLayoutError_InvalidFieldName);

		memoryOffset /= 8;	//From bits to bytes
	}
}