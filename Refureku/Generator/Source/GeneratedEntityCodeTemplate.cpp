#include "GeneratedEntityCodeTemplate.h"

using namespace rfk;

std::hash<std::string> GeneratedEntityCodeTemplate::_stringHasher;

std::string	GeneratedEntityCodeTemplate::fillEntityProperties(kodgen::EntityInfo const& info, std::string const& entityVarName) const noexcept
{
	std::string result;

	for (kodgen::SimpleProperty const& prop : info.properties.simpleProperties)
	{
		result += entityVarName + "properties.simpleProperties.emplace(\"" + prop.name + "\"); ";
	}

	for (kodgen::ComplexProperty const& prop : info.properties.complexProperties)
	{
		for (std::string subProp : prop.subProperties)
		{
			result += entityVarName + "properties.complexProperties.emplace(\"" + prop.name + "\", \"" + subProp + "\"); ";
		}
	}

	return result;
}