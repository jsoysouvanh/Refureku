#include "Parsing/EntityParser.h"

#include <algorithm>

#include "Properties/NativeProperties/NativeProperties.h"

using namespace kodgen;

void EntityParser::updateShouldParseAllNested(EntityInfo const& parsingEntity) noexcept
{
	getContext().shouldParseAllNested = std::find_if(parsingEntity.properties.simpleProperties.cbegin(), parsingEntity.properties.simpleProperties.cend(),
													 [](SimpleProperty const& prop) { return prop.mainProperty == NativeProperties::parseAllNestedProperty; })
												!= parsingEntity.properties.simpleProperties.cend();
}

void EntityParser::performFinalPropertiesCheck(EntityInfo const& entity) const noexcept
{
	std::string errorDescription;

	//Check validity with simple properties
	for (uint8 i = 0u; i < entity.properties.simpleProperties.size(); i++)
	{
		if (!entity.properties.simpleProperties[i].boundPropertyRule->isEntityValid(entity, i, errorDescription))
		{
			getContext().parsingResult->errors.emplace_back(errorDescription, clang_getCursorLocation(getContext().rootCursor));
		}
	}

	//Check validity with complex properties
	for (uint8 i = 0u; i < entity.properties.complexProperties.size(); i++)
	{
		if (!entity.properties.complexProperties[i].boundPropertyRule->isEntityValid(entity, i, errorDescription))
		{
			getContext().parsingResult->errors.emplace_back(errorDescription, clang_getCursorLocation(getContext().rootCursor));
		}
	}
}