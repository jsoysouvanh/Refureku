#include "Kodgen/Properties/PropertyParsingSettings.h"

using namespace kodgen;

void PropertyParsingSettings::loadSettings(toml::value const& table) noexcept
{
	TomlUtility::updateSetting(table, "propertySeparator", propertySeparator);
	TomlUtility::updateSetting(table, "subPropertySeparator", subPropertySeparator);
	TomlUtility::updateSetting(table, "subPropertyStartEncloser", subPropertyEnclosers[0]);
	TomlUtility::updateSetting(table, "subPropertyEndEncloser", subPropertyEnclosers[1]);
	TomlUtility::updateSetting(table, "ignoredCharacters", ignoredCharacters);

	TomlUtility::updateSetting(table, "namespaceMacroName", namespaceMacroName);
	TomlUtility::updateSetting(table, "classMacroName", classMacroName);
	TomlUtility::updateSetting(table, "structMacroName", structMacroName);
	TomlUtility::updateSetting(table, "fieldMacroName", fieldMacroName);
	TomlUtility::updateSetting(table, "methodMacroName", methodMacroName);
	TomlUtility::updateSetting(table, "enumMacroName", enumMacroName);
	TomlUtility::updateSetting(table, "enumValueMacroName", enumValueMacroName);
}