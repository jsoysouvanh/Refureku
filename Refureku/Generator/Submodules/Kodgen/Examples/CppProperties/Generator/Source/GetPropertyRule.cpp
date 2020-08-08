#include "GetPropertyRule.h"

#include <algorithm>

using namespace kodgen;

bool GetPropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EEntityType entityType) const noexcept
{
	return mainProperty == "Get" && entityType == EEntityType::Field;
}

bool GetPropertyRule::isSubPropSyntaxValid(std::string const& subProperty, uint8 /* subPropIndex */, std::string& out_errorDescription) const noexcept
{
	if (subProperty != "*" && subProperty != "&" && subProperty != "const" && subProperty != "explicit")
	{
		out_errorDescription = subProperty + " is not a valid subproperty.";

		return false;
	}

	return true;
}

bool GetPropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	ComplexProperty const& complexProp = propertyGroup.complexProperties[propertyIndex];

	//Can't have * and & at the same time
	if (std::find(complexProp.subProperties.cbegin(), complexProp.subProperties.cend(), "*") != complexProp.subProperties.cend() &&
		std::find(complexProp.subProperties.cbegin(), complexProp.subProperties.cend(), "&") != complexProp.subProperties.cend())
	{
		out_errorDescription = "Can't use * and & in the same time.";

		return false;
	}

	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}

bool GetPropertyRule::isEntityValid(EntityInfo const& /* entity */, uint8 /* propertyIndex */, std::string& /* out_errorDescription */) const noexcept
{
	//No specific check to perform here
	return true;
}