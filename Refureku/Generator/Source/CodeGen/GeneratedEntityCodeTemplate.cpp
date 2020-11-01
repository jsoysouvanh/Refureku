#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

#include <cassert>

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

std::string GeneratedEntityCodeTemplate::fillEntityProperties2(kodgen::EntityInfo const& info, std::string const& entityVarName) const noexcept
{
	std::string		result;
	std::string		propVarName;
	size_t			propsCount	= info.properties.simpleProperties.size() + info.properties.complexProperties.size();
	kodgen::uint8	index		= 0u;

	if (propsCount > 0)
	{
		//Reserve space to avoid reallocation
		result += entityVarName + "properties2.reserve(" + std::to_string(propsCount) + ");";

		//Add simple props
		for (kodgen::SimpleProperty const& prop : info.properties.simpleProperties)
		{
			result += addSimplePropertyToEntity(info, entityVarName, prop.mainProperty, index);

			index++;
		}

		//Add complex props
		for (kodgen::ComplexProperty const& prop : info.properties.complexProperties)
		{
			if (prop.subProperties.empty())
			{
				result += addSimplePropertyToEntity(info, entityVarName, prop.mainProperty, index);
			}
			else
			{
				result += addComplexPropertyToEntity(info, entityVarName, prop, index);
			}

			index++;
		}
	}

	return result;
}

std::string GeneratedEntityCodeTemplate::generatePropertyVariableName(kodgen::EntityInfo const& info, kodgen::uint8 propIndex) const noexcept
{
	return "property" + std::to_string(stringHasher(info.id)) + "_" + std::to_string(propIndex);
}

std::string GeneratedEntityCodeTemplate::addSimplePropertyToEntity(kodgen::EntityInfo const& info, std::string const& entityVarName, std::string const& propName, kodgen::uint8 propIndex) const noexcept
{
	std::string propVarName = generatePropertyVariableName(info, propIndex);
	std::string result;

	//static_assert((CustomProperty::targetEntityKind & rfk::Entity::EKind::Field) != rfk::Entity::EKind::Undefined, "A::field: CustomProperty can't be applied to a Field.");
	//TODO: static_assert targetEntityKind
	//TODO: static_assert allowMultiple

	//This static_assert is here just to issue an error if the propName doesn't exist or is not included
	result += "static_assert(sizeof(" + propName + ") != 0u, \"\");";

	result += "static " + propName + " " + propVarName + "; " + entityVarName + "properties2.emplace_back(&" + propVarName + "); ";

	return result;
}

std::string GeneratedEntityCodeTemplate::addComplexPropertyToEntity(kodgen::EntityInfo const& info, std::string const& entityVarName, kodgen::ComplexProperty const& prop, kodgen::uint8 propIndex) const noexcept
{
	assert(!prop.subProperties.empty());

	std::string propVarName = generatePropertyVariableName(info, propIndex);
	std::string result;
	
	//TODO: static_assert targetEntityKind
	//TODO: static_assert allowMultiple

	result += "static " + prop.mainProperty + " " + propVarName + "{";

	for (std::string subProp : prop.subProperties)
	{
		result += subProp + ",";
	}

	//Replace last , by closing }
	result.back() = '}';

	result.push_back(';');

	result += entityVarName + "properties2.emplace_back(&" + propVarName + "); ";

	return result;
}

void GeneratedEntityCodeTemplate::ifDefUndefMacro(kodgen::GeneratedFile& generatedFile, std::string const& macroName) const noexcept
{
	generatedFile.writeLines("#ifdef " + macroName,
							 "\t#undef " + macroName,
							 "#endif\n");
}