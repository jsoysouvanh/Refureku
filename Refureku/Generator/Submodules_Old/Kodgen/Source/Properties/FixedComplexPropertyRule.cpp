#include "Kodgen/Properties/FixedComplexPropertyRule.h"

using namespace kodgen;

FixedComplexPropertyRule::FixedComplexPropertyRule(std::string mainPropName, EEntityType validEntityTypes) noexcept:
	DefaultComplexPropertyRule(std::move(mainPropName), std::move(validEntityTypes))
{
}

bool FixedComplexPropertyRule::isSubPropSyntaxValid(std::string const& subProperty, uint8 subPropIndex, std::string& out_errorDescription) const noexcept
{
	if (subPropIndex >= subProperties.size())
	{
		out_errorDescription = "Only " + std::to_string(subProperties.size()) + " subproperties expected.";

		return false;
	}

	return subProperties[subPropIndex].isValid(subProperty, out_errorDescription);
}

bool FixedComplexPropertyRule::isPropertyGroupValid(PropertyGroup const& propertyGroup, uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	if (propertyGroup.complexProperties[propertyIndex].subProperties.size() != subProperties.size())
	{
		out_errorDescription = std::to_string(subProperties.size()) + " subproperties were expected but " + std::to_string(propertyGroup.complexProperties[propertyIndex].subProperties.size()) + " were found.";

		return false;
	}

	return true;
}