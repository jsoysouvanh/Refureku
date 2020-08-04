#include "Kodgen/Properties/NativeProperties/ParseAllNestedPropertyRule.h"

#include "Kodgen/Properties/NativeProperties/NativeProperties.h"

using namespace kodgen;

ParseAllNestedPropertyRule::ParseAllNestedPropertyRule() noexcept:
	DefaultSimplePropertyRule(NativeProperties::parseAllNestedProperty,
							  { EntityInfo::EType::Namespace, EntityInfo::EType::Struct, EntityInfo::EType::Class },
							  "Namespace, Struct and Class property. Indicates the generator to parse all direct nested entities without having to explicitly mark them with the macro.")
{
}

bool ParseAllNestedPropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}