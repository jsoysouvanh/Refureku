#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

using namespace rfk;

std::hash<std::string> const GeneratedEntityCodeTemplate::stringHasher;

std::string	GeneratedEntityCodeTemplate::fillEntityProperties(kodgen::EntityInfo const& info, std::string const& entityVarName) const noexcept
{
	std::string result;

	if (info.properties.simpleProperties.size() != 0u)
	{
		//Reserve space to avoid reallocation
		result += entityVarName + "properties.simpleProperties.reserve(" + std::to_string(info.properties.simpleProperties.size()) + ");";

		for (kodgen::SimpleProperty const& prop : info.properties.simpleProperties)
		{
			result += entityVarName + "properties.simpleProperties.emplace_back(R\"(" + prop.mainProperty + ")\"); ";
		}
	}

	if (info.properties.complexProperties.size() != 0u)
	{
		//Reserve space to avoid reallocation
		result += entityVarName + "properties.complexProperties.reserve(" + std::to_string(info.properties.complexProperties.size()) + ");";

		for (kodgen::ComplexProperty const& prop : info.properties.complexProperties)
		{
			result += entityVarName + "properties.complexProperties.emplace_back(R\"(" + prop.mainProperty + ")\", std::vector<std::string>({";

			if (prop.subProperties.size() != 0u)
			{
				for (std::string subProp : prop.subProperties)
				{
					result += "R\"(" + subProp + ")\",";
				}

				//Replace last string by closing }
				result.back() = '}';
			}
			else
			{
				result += "}";
			}
			

			result += "));";
		}
	}

	return result;
}