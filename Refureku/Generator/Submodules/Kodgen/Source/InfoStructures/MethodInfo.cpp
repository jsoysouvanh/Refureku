#include "InfoStructures/MethodInfo.h"

#include <algorithm>
#include <cassert>

using namespace kodgen;

MethodInfo::MethodInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EType::Method),
	qualifiers{false, false, false, false, false, false, false, false}
{
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