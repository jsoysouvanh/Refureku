#include "InfoStructures/FieldInfo.h"

using namespace kodgen;

FieldInfo::FieldInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup) noexcept:
	EntityInfo(cursor, std::forward<PropertyGroup>(propertyGroup), EType::Field),
	qualifiers{false, false},
	accessSpecifier{EAccessSpecifier::Invalid},
	memoryOffset{0}
{
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, FieldInfo const& fieldInfo) noexcept
{
	out_stream << fieldInfo.type << "   " << fieldInfo.name << "   " << fieldInfo.properties;

	return out_stream;
}