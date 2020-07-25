/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "Properties/PropertyRules.h"
#include "Misc/TomlUtility.h"

namespace kodgen
{
	class PropertyParsingSettings
	{
		public:
			/** Char used to separate two properties. */
			char						propertySeparator		= ',';

			/** Char used to separate two sub properties. */
			char						subPropertySeparator	= ',';

			/** Chars used to start and close respectively a group of sub properties. */
			char						subPropertyEnclosers[2]	= { '[', ']' };

			/** Collection of chars which will be ignored by the property parser. */
			std::unordered_set<char>	ignoredCharacters;

			/** Rules defining valid namespace properties. */
			PropertyRules				namespacePropertyRules	= PropertyRules("Namespace");

			/** Rules defining valid class properties. */
			PropertyRules				classPropertyRules		= PropertyRules("Class");

			/** Rules defininf valid struct properties. */
			PropertyRules				structPropertyRules		= PropertyRules("Struct");

			/** Rules defininf valid field properties. */
			PropertyRules				fieldPropertyRules		= PropertyRules("Field");
			
			/** Rules defininf valid method properties. */
			PropertyRules				methodPropertyRules		= PropertyRules("Method");
			
			/** Rules defininf valid enum properties. */
			PropertyRules				enumPropertyRules		= PropertyRules("Enum");
			
			/** Rules defininf valid enum value properties. */
			PropertyRules				enumValuePropertyRules	= PropertyRules("EnumVal");

			/**
			*	@brief Load settings from a TOML file.
			*	
			*	@param table TOML file table to look into.
			*/
			void	loadSettings(toml::value const& table)	noexcept;
	};
}