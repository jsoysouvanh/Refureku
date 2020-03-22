#include "Parsing/PropertyParser.h"

#include <cassert>

using namespace kodgen;

opt::optional<PropertyGroup> PropertyParser::getProperties(std::string&& annotateMessage, std::string const& annotationId, PropertyRules const& rules) noexcept
{
	if (annotateMessage.substr(0, annotationId.size()) == annotationId)
	{
		if (splitProperties(annotateMessage.substr(annotationId.size())))
		{
			return checkAndFillPropertyGroup(_splitProps, rules);
		}
	}
	else
	{
		//Tried to add properties to a class with the wrong macro
		_parsingError = EParsingError::WrongPropertyMacroUsed;
	}

	assert(_parsingError != EParsingError::Count);	//If fails, _parsing error must be updated
	return opt::nullopt;
}

opt::optional<PropertyGroup> PropertyParser::getClassProperties(std::string&& annotateMessage) noexcept
{
	static std::string classAnnotation = "KGC:";

	return getProperties(std::forward<std::string>(annotateMessage), classAnnotation, _propertyParsingSettings->classPropertyRules);
}

opt::optional<PropertyGroup> PropertyParser::getStructProperties(std::string&& annotateMessage) noexcept
{
	static std::string structAnnotation = "KGS:";

	return getProperties(std::forward<std::string>(annotateMessage), structAnnotation, _propertyParsingSettings->structPropertyRules);
}

opt::optional<PropertyGroup> PropertyParser::getFieldProperties(std::string&& annotateMessage) noexcept
{
	static std::string fieldAnnotation = "KGF:";

	return getProperties(std::forward<std::string>(annotateMessage), fieldAnnotation, _propertyParsingSettings->fieldPropertyRules);
}

opt::optional<PropertyGroup> PropertyParser::getMethodProperties(std::string&& annotateMessage) noexcept
{
	static std::string methodAnnotation = "KGM:";

	return getProperties(std::forward<std::string>(annotateMessage), methodAnnotation, _propertyParsingSettings->methodPropertyRules);
}

opt::optional<PropertyGroup> PropertyParser::getEnumProperties(std::string&& annotateMessage) noexcept
{
	static std::string enumAnnotation = "KGE:";

	return getProperties(std::forward<std::string>(annotateMessage), enumAnnotation, _propertyParsingSettings->enumPropertyRules);
}

opt::optional<PropertyGroup> PropertyParser::getEnumValueProperties(std::string&& annotateMessage) noexcept
{
	static std::string enumValueAnnotation = "KGEV:";

	return getProperties(std::forward<std::string>(annotateMessage), enumValueAnnotation, _propertyParsingSettings->enumValuePropertyRules);
}

bool PropertyParser::splitProperties(std::string&& propertiesString) noexcept
{
	cleanString(propertiesString);

	bool isParsingSubproperty = false;

	while (!propertiesString.empty())
	{
		if (isParsingSubproperty)
		{
			if (!lookForNextSubProp(propertiesString, isParsingSubproperty))
			{
				return false;
			}
		}
		else if (!lookForNextProp(propertiesString, isParsingSubproperty))
		{
			return false;
		}
	}

	//propertyString has been fully parsed but no end subproperty mark found
	if (isParsingSubproperty)
	{
		_parsingError = EParsingError::SubPropertyEndEncloserMissing;
		return false;
	}

	return true;
}

bool PropertyParser::lookForNextProp(std::string& inout_parsingProps, bool& out_isParsingSubProp)
{
	//Find first occurence of propertySeparator or subprop start encloser in string
	size_t index = inout_parsingProps.find_first_of(_relevantCharsForPropParsing);

	//Was last prop
	if (index == inout_parsingProps.npos)
	{
		_splitProps.push_back({ inout_parsingProps });
		inout_parsingProps.clear();
	}
	else if (inout_parsingProps[index] == _propertyParsingSettings->propertySeparator)
	{
		_splitProps.push_back({ std::string(inout_parsingProps.cbegin(), inout_parsingProps.cbegin() + index) });
		inout_parsingProps.erase(0, index + 1);
	}
	else	//_propertyParsingSettings->subPropertyEnclosers[0]
	{
		out_isParsingSubProp = true;

		_splitProps.push_back({ std::string(inout_parsingProps.cbegin(), inout_parsingProps.cbegin() + index) });
		inout_parsingProps.erase(0, index + 1);
	}

	return true;
}

bool PropertyParser::lookForNextSubProp(std::string& inout_parsingProps, bool& out_isParsingSubProp)
{
	//Find first occurence of propertySeparator or subprop start encloser in string
	size_t index = inout_parsingProps.find_first_of(_relevantCharsForSubPropParsing);

	//Was last prop
	if (index == inout_parsingProps.npos)
	{
		_parsingError = EParsingError::SubPropertyEndEncloserMissing;
		return false;
	}
	else if (inout_parsingProps[index] == _propertyParsingSettings->subPropertySeparator)
	{
		_splitProps.back().push_back(std::string(inout_parsingProps.cbegin(), inout_parsingProps.cbegin() + index));
		inout_parsingProps.erase(0, index + 1);
	}
	else	//_propertyParsingSettings->subPropertyEnclosers[1]
	{
		//Make sure there is a property separator after the end encloser if is not the last char of the string
		if (index != inout_parsingProps.size() - 1 && inout_parsingProps[index + 1] != _propertyParsingSettings->propertySeparator)
		{
			_parsingError = EParsingError::PropertySeparatorMissing;
			return false;
		}

		out_isParsingSubProp = false;

		_splitProps.back().push_back(std::string(inout_parsingProps.cbegin(), inout_parsingProps.cbegin() + index));
		inout_parsingProps.erase(0, index + 2);	// + 2 to consume subprop end encloser and prop separator
	}

	return true;
}

void PropertyParser::cleanString(std::string& toCleanString) const noexcept
{
	for (char toRemoveChar : _propertyParsingSettings->ignoredCharacters)
	{
		toCleanString.erase(std::remove(toCleanString.begin(), toCleanString.end(), toRemoveChar), toCleanString.end());
	}
}

opt::optional<PropertyGroup> PropertyParser::checkAndFillPropertyGroup(std::vector<std::vector<std::string>>& splitProps, PropertyRules const& rules) noexcept
{
	PropertyGroup propertyGroup;

	for (std::vector<std::string>& props : splitProps)
	{
		//Expect a simple prop
		if (props.size() == 1)
		{
			if (!addSimpleProperty(props, rules, propertyGroup))
			{
				return opt::nullopt;
			}
		}
		//Expect a complex prop
		else if (!addComplexProperty(props, rules, propertyGroup))
		{
			return opt::nullopt;
		}
	}

	return propertyGroup;
}

bool PropertyParser::addSimpleProperty(std::vector<std::string>& propertyAsVector, PropertyRules const& rules, PropertyGroup& out_propertyGroup) noexcept
{
	std::string propName = std::move(propertyAsVector[0]);

	if (rules.getSimplePropertyRule(propName) != nullptr)
	{
		out_propertyGroup.simpleProperties.emplace_back(SimpleProperty(std::move(propName)));
		return true;
	}
	else
	{
		_parsingError = EParsingError::InvalidSimpleProperty;
		return false;
	}
}

bool PropertyParser::addComplexProperty(std::vector<std::string>& propertyAsVector, PropertyRules const& rules, PropertyGroup& out_propertyGroup) noexcept
{
	std::string mainProp = std::move(propertyAsVector[0]);

	if (ComplexPropertyRule const* propertyRule = rules.getComplexPropertyRule(mainProp))
	{
		ComplexProperty complexProp;
		complexProp.name = std::move(mainProp);

		//Iterate over subproperties
		for (uint8 i = 1u; i < propertyAsVector.size(); i++)
		{
			std::string subProp = std::move(propertyAsVector[i]);

			if (propertyRule->isValidSubProperty(subProp))
			{
				complexProp.subProperties.emplace_back(std::move(subProp));
			}
			else if (subProp.empty() && propertyAsVector.size() == 2)
			{
				//If there is a single empty subprop, means there is no subprop at all
			}
			else
			{
				_parsingError = EParsingError::InvalidComplexSubProperty;
				return false;
			}
		}

		out_propertyGroup.complexProperties.emplace_back(std::move(complexProp));
	}
	else
	{
		_parsingError = EParsingError::InvalidComplexMainProperty;
		return false;
	}

	return true;
}

void PropertyParser::setup(PropertyParsingSettings const* propertyParsingSettings) noexcept
{
	_propertyParsingSettings = propertyParsingSettings;

	char charsForPropParsing[] =	{
		_propertyParsingSettings->propertySeparator,
		_propertyParsingSettings->subPropertyEnclosers[0]
	};

	char charsForSubPropParsing[] =	{
		_propertyParsingSettings->subPropertySeparator,
		_propertyParsingSettings->subPropertyEnclosers[1]
	};

	_relevantCharsForPropParsing = std::string(charsForPropParsing, 2);
	_relevantCharsForSubPropParsing = std::string(charsForSubPropParsing, 2);
}

void PropertyParser::clean() noexcept
{
	_splitProps.clear();
	_parsingError = EParsingError::Count;
}

EParsingError PropertyParser::getParsingError() const noexcept
{
	return _parsingError;
}