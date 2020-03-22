#pragma once

#include <unordered_set>

#include "Properties/PropertyRules.h"

namespace kodgen
{
	struct PropertyParsingSettings
	{
		char						propertySeparator		= ',';
		char						subPropertySeparator	= ',';
		char						subPropertyEnclosers[2]	= { '[', ']' };
		std::unordered_set<char>	ignoredCharacters;

		PropertyRules				classPropertyRules		= PropertyRules("Class");
		PropertyRules				structPropertyRules		= PropertyRules("Struct");
		PropertyRules				fieldPropertyRules		= PropertyRules("Field");
		PropertyRules				methodPropertyRules		= PropertyRules("Method");
		PropertyRules				enumPropertyRules		= PropertyRules("Enum");
		PropertyRules				enumValuePropertyRules	= PropertyRules("EnumVal");
	};
}