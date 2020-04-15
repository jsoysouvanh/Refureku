#include "Properties/PropertyRules.h"

#include <algorithm>

#include "Misc/TomlUtility.h"

using namespace kodgen;

PropertyRules::PropertyRules(std::string defaultMacroName):
	macroName{std::move(defaultMacroName)}
{
}

bool PropertyRules::addSimplePropertyRule(std::string&& propertyName) noexcept
{
	return _simplePropertyRules.emplace(SimplePropertyRule(std::forward<std::string>(propertyName))).second;
}

bool PropertyRules::removeSimplePropertyRule(std::string&& propertyName) noexcept
{
	std::set<SimplePropertyRule>::const_iterator it = _simplePropertyRules.find(SimplePropertyRule(std::forward<std::string>(propertyName)));

	if (it != _simplePropertyRules.cend())
	{
		_simplePropertyRules.erase(it);
		
		return true;
	}

	return false;
}

bool PropertyRules::addComplexPropertyRule(std::string&& mainPropertyName, std::string&& subPropPattern) noexcept
{
	return _complexPropertyRules.insert(ComplexPropertyRule(std::forward<std::string>(mainPropertyName), std::forward<std::string>(subPropPattern))).second;
}

bool PropertyRules::removeComplexPropertyRule(std::string&& mainPropertyName, std::string&& subPropPattern) noexcept
{
	std::set<ComplexPropertyRule>::const_iterator it = _complexPropertyRules.find(ComplexPropertyRule(std::forward<std::string>(mainPropertyName), std::forward<std::string>(subPropPattern)));

	if (it != _complexPropertyRules.cend())
	{
		_complexPropertyRules.erase(it);

		return true;
	}

	return false;
}

bool PropertyRules::removeComplexPropertyRule(std::string&& mainPropertyName) noexcept
{
	decltype(_complexPropertyRules)::const_iterator it = std::find_if(_complexPropertyRules.cbegin(), _complexPropertyRules.cend(), [mainPropertyName](ComplexPropertyRule const& prop) { return prop.name == mainPropertyName; });

	if (it != _complexPropertyRules.cend())
	{
		_complexPropertyRules.erase(it);

		return true;
	}

	return false;
}

void PropertyRules::clearSimplePropertyRules() noexcept
{
	_simplePropertyRules.clear();
}

void PropertyRules::clearComplexPropertyRules() noexcept
{
	_complexPropertyRules.clear();
}

void PropertyRules::clearAllPropertyRules() noexcept
{
	clearSimplePropertyRules();
	clearComplexPropertyRules();
}

SimplePropertyRule const* PropertyRules::getSimplePropertyRule(std::string const& propertyName) const noexcept
{
	decltype(_simplePropertyRules)::const_iterator it = std::find_if(_simplePropertyRules.cbegin(), _simplePropertyRules.cend(), [propertyName](SimplePropertyRule const& prop) { return prop.name == propertyName; });

	return (it != _simplePropertyRules.cend()) ? &*it : nullptr;
}

ComplexPropertyRule const* PropertyRules::getComplexPropertyRule(std::string const& propertyName) const noexcept
{
	decltype(_complexPropertyRules)::const_iterator it = std::find_if(_complexPropertyRules.cbegin(), _complexPropertyRules.cend(), [propertyName](ComplexPropertyRule const& prop) { return prop.name == propertyName; });

	return (it != _complexPropertyRules.cend()) ? &*it : nullptr;
}

void PropertyRules::loadSettings(toml::value const& table) noexcept
{
	TomlUtility::updateSetting(table, "macroName", macroName);

	//TODO properties?
}