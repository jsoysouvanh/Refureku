#include "Properties/NativeProperties/ParseAllNestedPropertyRule.h"

#include "Properties/NativeProperties/NativeProperties.h"

using namespace kodgen;

bool ParseAllNestedPropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EntityInfo::EType entityType) const noexcept
{
	return mainProperty == NativeProperties::parseAllNestedProperty &&
		(entityType == EntityInfo::EType::Namespace || entityType == EntityInfo::EType::Class || entityType == EntityInfo::EType::Struct);
}

bool ParseAllNestedPropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}

bool ParseAllNestedPropertyRule::isEntityValid(EntityInfo const& /* entity */, uint8 /* propertyIndex */, std::string& /* out_errorDescription */) const noexcept
{
	//Nothing special to check
	return true;
}