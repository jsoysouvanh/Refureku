#include "Properties/PropertyParsingSettings.h"

using namespace kodgen;

void PropertyParsingSettings::loadSettings(toml::value const& table) noexcept
{
	TomlUtility::updateSetting(table, "propertySeparator", propertySeparator);
	TomlUtility::updateSetting(table, "subPropertySeparator", subPropertySeparator);
	TomlUtility::updateSetting(table, "subPropertyStartEncloser", subPropertyEnclosers[0]);
	TomlUtility::updateSetting(table, "subPropertyEndEncloser", subPropertyEnclosers[1]);
	TomlUtility::updateSetting(table, "ignoredCharacters", ignoredCharacters);

	if (table.contains("Class"))
	{
		classPropertyRules.loadSettings(toml::find(table, "Class"));
	}

	if (table.contains("Struct"))
	{
		structPropertyRules.loadSettings(toml::find(table, "Struct"));
	}

	if (table.contains("Field"))
	{
		fieldPropertyRules.loadSettings(toml::find(table, "Field"));
	}

	if (table.contains("Method"))
	{
		methodPropertyRules.loadSettings(toml::find(table, "Method"));
	}

	if (table.contains("Enum"))
	{
		enumPropertyRules.loadSettings(toml::find(table, "Enum"));
	}

	if (table.contains("EnumValue"))
	{
		enumValuePropertyRules.loadSettings(toml::find(table, "EnumValue"));
	}
}