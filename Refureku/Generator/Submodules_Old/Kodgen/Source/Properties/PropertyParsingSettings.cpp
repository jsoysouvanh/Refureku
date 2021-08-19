#include "Kodgen/Properties/PropertyParsingSettings.h"

using namespace kodgen;

void PropertyParsingSettings::loadSettings(toml::value const& table, ILogger* logger) noexcept
{
	TomlUtility::updateSetting(table, "propertySeparator", propertySeparator, logger);
	TomlUtility::updateSetting(table, "subPropertySeparator", subPropertySeparator, logger);
	TomlUtility::updateSetting(table, "subPropertyStartEncloser", subPropertyEnclosers[0], logger);
	TomlUtility::updateSetting(table, "subPropertyEndEncloser", subPropertyEnclosers[1], logger);

	TomlUtility::updateSetting(table, "namespaceMacroName", namespaceMacroName, logger);
	TomlUtility::updateSetting(table, "classMacroName", classMacroName, logger);
	TomlUtility::updateSetting(table, "structMacroName", structMacroName, logger);
	TomlUtility::updateSetting(table, "variableMacroName", variableMacroName, logger);
	TomlUtility::updateSetting(table, "fieldMacroName", fieldMacroName, logger);
	TomlUtility::updateSetting(table, "functionMacroName", functionMacroName, logger);
	TomlUtility::updateSetting(table, "methodMacroName", methodMacroName, logger);
	TomlUtility::updateSetting(table, "enumMacroName", enumMacroName, logger);
	TomlUtility::updateSetting(table, "enumValueMacroName", enumValueMacroName, logger);
}