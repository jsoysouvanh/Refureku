#include "Properties/NativeProperties/GenCodeTemplatePropertyRule.h"

#include "Properties/NativeProperties/NativeProperties.h"

using namespace kodgen;

bool GenCodeTemplatePropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EntityInfo::EType /* entityType */) const noexcept
{
	return mainProperty == NativeProperties::generatedCodeTemplateProperty;
}

bool GenCodeTemplatePropertyRule::isSubPropSyntaxValid(std::string const& subProperty, uint8 /* subPropIndex */, std::string& out_errorDescription) const noexcept
{
	if (validTemplateNames.find(subProperty) == validTemplateNames.cend())
	{
		out_errorDescription = "The provided generated code template has not been registered to the FileGenerator.";

		return false;
	}

	return true;
}

bool GenCodeTemplatePropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return	hasValidSubpropCount(propertyGroup, propertyIndex, 1u, out_errorDescription) &&
			isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}