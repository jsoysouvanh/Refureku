#include "Kodgen/Properties/NativeProperties/ParseAllNestedPropertyRule.h"

#include "Kodgen/Properties/NativeProperties/NativeProperties.h"

using namespace kodgen;

ParseAllNestedPropertyRule::ParseAllNestedPropertyRule() noexcept:
	DefaultSimplePropertyRule(NativeProperties::parseAllNestedProperty,
							  EEntityType::Namespace | EEntityType::Struct | EEntityType::Class)
{
}

bool ParseAllNestedPropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}