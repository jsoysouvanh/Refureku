#include "Parsing/EntityParser.h"

#include <algorithm>

#include "Properties/NativeProperties.h"

using namespace kodgen;

void EntityParser::updateShouldParseAllNested(EntityInfo const& parsingEntity) noexcept
{
	getContext().shouldParseAllNested = std::find_if(parsingEntity.properties.simpleProperties.cbegin(), parsingEntity.properties.simpleProperties.cend(),
													 [](SimpleProperty const& prop) { return prop.name == NativeProperties::parseAllNestedProperty; })
												!= parsingEntity.properties.simpleProperties.cend();
}