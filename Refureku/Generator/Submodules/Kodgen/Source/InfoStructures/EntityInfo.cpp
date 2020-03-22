#include "InfoStructures/EntityInfo.h"

using namespace kodgen;

EntityInfo::EntityInfo(std::string&& entityName, PropertyGroup&& propertyGroup, EType&& entityType) noexcept:
	entityType{std::forward<EType>(entityType)},
	name{std::forward<std::string>(entityName)}, 
	properties{std::forward<PropertyGroup>(propertyGroup)}
{
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, EntityInfo const& entityInfo) noexcept
{
	out_stream << entityInfo.name;

	return out_stream;
}