#include "RefurekuGenerator/Properties/RangePropertyRule.h"

#include <Kodgen/InfoStructures/FieldInfo.h>

using namespace rfk;

RangePropertyRule::RangePropertyRule() noexcept:
	kodgen::FixedComplexPropertyRule("Range", kodgen::EEntityType::Field, "Defines a float range between min and max.")
{
	subProperties.emplace_back(kodgen::ComplexPropertySubProperty::EType::Float, "min", "Minimum of the range.");
	subProperties.emplace_back(kodgen::ComplexPropertySubProperty::EType::Float, "max", "Maximum of the range.");
}

bool RangePropertyRule::isPropertyGroupValid(kodgen::PropertyGroup const& propertyGroup, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	kodgen::ComplexProperty const& prop = propertyGroup.complexProperties[propertyIndex];

	//Parent implementation checks subprop count
	if (FixedComplexPropertyRule::isPropertyGroupValid(propertyGroup, propertyIndex, out_errorDescription))
	{
		//Make sure min < max
		if (std::stof(prop.subProperties[0]) > std::stof(prop.subProperties[1]))
		{
			out_errorDescription = "First subproperty (min) should be less or equal than second subproperty (max)";

			return false;
		}
	}

	return true;
}

bool RangePropertyRule::isEntityValid(kodgen::EntityInfo const& entity, kodgen::uint8 /* propertyIndex */, std::string& out_errorDescription) const noexcept
{
	//Range can apply only on floats
	if (static_cast<kodgen::FieldInfo const&>(entity).type.getCanonicalName(true) != "float")
	{
		out_errorDescription = "Range property can only apply on float fields.";

		return false;
	}

	return true;
}