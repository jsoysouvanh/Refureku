#include "Properties/ComplexPropertyRule.h"

using namespace kodgen;

bool ComplexPropertyRule::isUsedOnlyOnce(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	for (uint8 i = 0u; i < propertyGroup.complexProperties.size(); i++)
	{
		if (i != propertyIndex && propertyGroup.complexProperties[i].boundPropertyRule == this)
		{
			out_errorDescription = "Property \"" + propertyGroup.complexProperties[i].mainProperty + "\" is used more than once in the property group.";

			return false;
		}
	}

	return true;
}

bool ComplexPropertyRule::hasValidSubpropCount(PropertyGroup const& propertyGroup, uint8 propertyIndex, uint8 validCount, std::string& out_errorDescription) const noexcept
{
	size_t subpropsCount = propertyGroup.complexProperties[propertyIndex].subProperties.size();

	if (subpropsCount != validCount)
	{
		out_errorDescription = "Expected " + std::to_string(validCount) + " subproperties but " + std::to_string(subpropsCount) + " provided."; 
		
		return false;
	}

	return true;
}