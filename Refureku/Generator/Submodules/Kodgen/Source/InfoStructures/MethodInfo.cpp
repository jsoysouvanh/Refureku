#include "InfoStructures/MethodInfo.h"

#include <algorithm>
#include <cassert>

#include "Misc/Helpers.h"

using namespace kodgen;

MethodInfo::MethodInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EType::Method),
	qualifiers{	clang_CXXMethod_isDefaulted(cursor) != 0u,
				clang_CXXMethod_isStatic(cursor) != 0u,
				clang_CXXMethod_isVirtual(cursor) != 0u,
				clang_CXXMethod_isPureVirtual(cursor) != 0u,
				clang_Cursor_isFunctionInlined(cursor) != 0u,
				false,
				false,
				clang_CXXMethod_isConst(cursor) != 0u}
{
	CXType methodType = clang_getCursorType(cursor);

	assert(methodType.kind == CXTypeKind::CXType_FunctionProto);

	//Define prototype
	prototype	= Helpers::getString(clang_getTypeSpelling(methodType));

	//Define return type
	returnType	= TypeInfo(clang_getResultType(methodType));
}

std::string MethodInfo::getName() const noexcept
{
	//Remove arguments (...)
	return name.substr(0, name.find_first_of('('));
}

std::string MethodInfo::getPrototype(bool removeQualifiers, bool removeSpaces) const noexcept
{
	std::string result(prototype);

	//Back is not ')', we have things to remove
	if (removeQualifiers && result.back() != ')')
	{
		size_t removeFrom = result.find_last_of(')');

		assert(removeFrom != std::string::npos);

		result.erase(removeFrom + 1);
	}

	if (removeSpaces)
	{
		result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
	}

	return result;
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, MethodInfo const& methodInfo) noexcept
{
	out_stream << methodInfo.returnType << "   " << methodInfo.name << "   " << methodInfo.properties;

	return out_stream;
}