#include "Kodgen/Properties/SimplePropertyRule.h"

using namespace kodgen;

bool SimplePropertyRule::isPropertyGroupValid(PropertyGroup const& /* propertyGroup */, uint8 /* propertyIndex */, std::string& /* out_errorDescription */) const noexcept
{
	//Is valid by default, so that override is not necessary in children
	return true;
}

bool SimplePropertyRule::isEntityValid(EntityInfo const& /* entity */, uint8 /* propertyIndex */, std::string& /* out_errorDescription */) const noexcept
{
	//Is valid by default, so that override is not necessary in children
	return true;
}

bool SimplePropertyRule::isUsedOnlyOnce(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	for (uint8 i = 0u; i < propertyGroup.simpleProperties.size(); i++)
	{
		if (i != propertyIndex && propertyGroup.simpleProperties[i].boundPropertyRule == this)
		{
			out_errorDescription = "The property \"" + propertyGroup.simpleProperties[i].mainProperty + "\" is used more than once in the property group.";

			return false;
		}
	}

	return true;
}

std::string	SimplePropertyRule::generateCode(EntityInfo const& /* entity */, Property const& /* property */, void* /* userData */) const noexcept
{
	//Default implementation does not generate any code
	return "";
}