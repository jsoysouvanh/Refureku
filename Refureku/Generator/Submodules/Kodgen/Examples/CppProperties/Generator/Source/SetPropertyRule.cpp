#include "SetPropertyRule.h"

using namespace kodgen;

bool SetPropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EntityInfo::EType entityType) const noexcept
{
	return mainProperty == "Set" && entityType == EntityInfo::EType::Field;
}

bool SetPropertyRule::isSubPropSyntaxValid(std::string const& subProperty, uint8 /* subPropIndex */, std::string& out_errorDescription) const noexcept
{
	if (subProperty != "explicit")
	{
		out_errorDescription = subProperty + " is not a valid subproperty.";

		return false;
	}

	return true;
}

bool SetPropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}

bool SetPropertyRule::isEntityValid(EntityInfo const& /* entity */, uint8 /* propertyIndex */, std::string& /* out_errorDescription */) const noexcept
{
	//No specific check to perform here
	return true;
}