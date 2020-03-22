#include "InfoStructures/MethodInfo.h"

using namespace kodgen;

MethodInfo::MethodInfo(std::string&& entityName, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(entityName.substr(0, entityName.find_first_of('(')), std::forward<PropertyGroup>(propertyGroup), EType::Method),
	qualifiers{false, false, false, false, false, false, false, false}
{
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, MethodInfo const& methodInfo) noexcept
{
	out_stream << methodInfo.returnType << "   " << methodInfo.name << "   " << methodInfo.properties;

	return out_stream;
}