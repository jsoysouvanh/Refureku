#include "Properties/FixedComplexPropertyRule.h"

using namespace kodgen;

FixedComplexPropertyRule::FixedComplexPropertyRule(std::string mainPropName, std::unordered_set<EntityInfo::EType> validEntityTypes, std::string description) noexcept:
	DefaultComplexPropertyRule(std::move(mainPropName), std::move(validEntityTypes), description)
{
}

std::string	FixedComplexPropertyRule::getMacroDocumentation() const noexcept
{
	std::string documentation = "/**\n"
								"*\t@brief " + getDescription() + "\n*\n";

	for (ComplexPropertySubProperty const& subprop : subProperties)
	{
		documentation += "*\t@param " + subprop.getName() + "\t" + toString(subprop.getType()) + " " + subprop.getDescription() + "\n";
	}

	return documentation + "*/";
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

std::string	FixedComplexPropertyRule::getMacroDefinition() const noexcept
{
	std::string macroDefinition = "#define " + mainPropName + "(";

	for (size_t i = 0u; i < subProperties.size(); i++)
	{
		macroDefinition += subProperties[i].getName() + ",";
	}

	//Replace last , by closing )
	macroDefinition.back() = ')';

	return	getMacroDocumentation() + "\n" + macroDefinition;
}