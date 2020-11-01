#include "Kodgen/Parsing/EntityParser.h"

#include <algorithm>

#include "Kodgen/Properties/NativeProperties/NativeProperties.h"

using namespace kodgen;

void EntityParser::updateShouldParseAllNested(EntityInfo const& parsingEntity) noexcept
{
	getContext().shouldParseAllNested = std::find_if(parsingEntity.properties.simpleProperties.cbegin(), parsingEntity.properties.simpleProperties.cend(),
													 [](SimpleProperty const& prop) { return prop.mainProperty == NativeProperties::parseAllNestedProperty; })
												!= parsingEntity.properties.simpleProperties.cend();
}

void EntityParser::performFinalPropertiesCheck(EntityInfo& entity) const noexcept
{
	std::string					errorDescription;
	SimplePropertyRule const*	propertyRule;

	//Check validity with simple properties
	for (uint8 i = 0u; i < entity.properties.simpleProperties.size(); i++)
	{
		propertyRule = entity.properties.simpleProperties[i].boundPropertyRule;

		if (propertyRule != nullptr && !propertyRule->isEntityValid(entity, i, errorDescription))
		{
			entity.properties.simpleProperties[i].boundPropertyRule = nullptr;
		}
	}

	//Check validity with complex properties
	for (uint8 i = 0u; i < entity.properties.complexProperties.size(); i++)
	{
		propertyRule = entity.properties.complexProperties[i].boundPropertyRule;

		if (propertyRule != nullptr && !propertyRule->isEntityValid(entity, i, errorDescription))
		{
			entity.properties.complexProperties[i].boundPropertyRule = nullptr;
		}
	}
}