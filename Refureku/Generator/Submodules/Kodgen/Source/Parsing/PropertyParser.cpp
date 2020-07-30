#include "Parsing/PropertyParser.h"

#include <cassert>

#include "Properties/SimpleProperty.h"
#include "Properties/ComplexProperty.h"

using namespace kodgen;

opt::optional<PropertyGroup> PropertyParser::getProperties(std::string&& annotateMessage, std::string const& annotationId, EntityInfo::EType entityType) noexcept
{
	if (annotateMessage.substr(0, annotationId.size()) == annotationId)
	{
		if (splitProperties(annotateMessage.substr(annotationId.size())))
		{
			if (opt::optional<PropertyGroup> propertyGroup = checkAndFillPropertyGroup(_splitProps, entityType))
			{
				//Check whole propertyGroup validity
				for (uint8 i = 0u; i < propertyGroup->simpleProperties.size(); i++)
				{
					if (!propertyGroup->simpleProperties[i].boundPropertyRule->isPropertyGroupValid(*propertyGroup, i, _parsingErrorDescription))
					{
						return opt::nullopt;
					}
				}

				for (uint8 i = 0u; i < propertyGroup->complexProperties.size(); i++)
				{
					if (!propertyGroup->complexProperties[i].boundPropertyRule->isPropertyGroupValid(*propertyGroup, i, _parsingErrorDescription))
					{
						return opt::nullopt;
					}
				}

				return propertyGroup;
			}
			else
			{
				return opt::nullopt;
			}
		}
	}
	else
	{
		_parsingErrorDescription = "The wrong macro has been used to attached properties to an entity.";
	}

	assert(!_parsingErrorDescription.empty());	//If fails, _parsingErrorDescription must be updated
	return opt::nullopt;
}

opt::optional<PropertyGroup> PropertyParser::getNamespaceProperties(std::string annotateMessage) noexcept
{
	static std::string namespaceAnnotation = "KGN:";

	return getProperties(std::move(annotateMessage), namespaceAnnotation, EntityInfo::EType::Namespace);
}

opt::optional<PropertyGroup> PropertyParser::getClassProperties(std::string annotateMessage) noexcept
{
	static std::string classAnnotation = "KGC:";

	return getProperties(std::move(annotateMessage), classAnnotation, EntityInfo::EType::Class);
}

opt::optional<PropertyGroup> PropertyParser::getStructProperties(std::string annotateMessage) noexcept
{
	static std::string structAnnotation = "KGS:";

	return getProperties(std::move(annotateMessage), structAnnotation, EntityInfo::EType::Struct);
}

opt::optional<PropertyGroup> PropertyParser::getFieldProperties(std::string annotateMessage) noexcept
{
	static std::string fieldAnnotation = "KGF:";

	return getProperties(std::move(annotateMessage), fieldAnnotation, EntityInfo::EType::Field);
}

opt::optional<PropertyGroup> PropertyParser::getMethodProperties(std::string annotateMessage) noexcept
{
	static std::string methodAnnotation = "KGM:";

	return getProperties(std::move(annotateMessage), methodAnnotation, EntityInfo::EType::Method);
}

opt::optional<PropertyGroup> PropertyParser::getEnumProperties(std::string annotateMessage) noexcept
{
	static std::string enumAnnotation = "KGE:";

	return getProperties(std::move(annotateMessage), enumAnnotation, EntityInfo::EType::Enum);
}

opt::optional<PropertyGroup> PropertyParser::getEnumValueProperties(std::string annotateMessage) noexcept
{
	static std::string enumValueAnnotation = "KGEV:";

	return getProperties(std::move(annotateMessage), enumValueAnnotation, EntityInfo::EType::EnumValue);
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
		_parsingErrorDescription = "Subproperty end encloser \"" + std::string(1u, _propertyParsingSettings->subPropertyEnclosers[1]) + "\" is missing.";
		
		return false;
	}

	return true;
}

bool PropertyParser::lookForNextProp(std::string& inout_parsingProps, bool& out_isParsingSubProp) noexcept
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

bool PropertyParser::lookForNextSubProp(std::string& inout_parsingProps, bool& out_isParsingSubProp) noexcept
{
	//Find first occurence of propertySeparator or subprop start encloser in string
	size_t index = inout_parsingProps.find_first_of(_relevantCharsForSubPropParsing);

	//Was last prop
	if (index == inout_parsingProps.npos)
	{
		_parsingErrorDescription = "Subproperty end encloser \"" + std::string(1u, _propertyParsingSettings->subPropertyEnclosers[1]) + "\" is missing.";

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
			_parsingErrorDescription = "Property separator \"" + std::string(1, _propertyParsingSettings->propertySeparator) + "\" is missing between two properties.";
			
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

opt::optional<PropertyGroup> PropertyParser::checkAndFillPropertyGroup(std::vector<std::vector<std::string>>& splitProps, EntityInfo::EType entityType) noexcept
{
	PropertyGroup propertyGroup;

	for (std::vector<std::string>& props : splitProps)
	{
		//Expect a simple prop
		if (props.size() == 1u)
		{
			if (!addSimpleProperty(props, entityType, propertyGroup))
			{
				return opt::nullopt;
			}
		}
		//Expect a complex prop
		else if (!addComplexProperty(props, entityType, propertyGroup))
		{
			return opt::nullopt;
		}
	}

	return propertyGroup;
}

bool PropertyParser::addSimpleProperty(std::vector<std::string>& propertyAsVector, EntityInfo::EType entityType, PropertyGroup& out_propertyGroup) noexcept
{
	std::string propName = std::move(propertyAsVector[0]);

	//Search the first simple property rule matching with the given name and entity type
	//Iterate backwards because native properties are at the end and a user rule should never override a native rule
	for (decltype(_propertyParsingSettings->simplePropertyRules)::const_reverse_iterator it = _propertyParsingSettings->simplePropertyRules.crbegin(); it != _propertyParsingSettings->simplePropertyRules.crend(); it++)
	{
		if ((*it)->isMainPropSyntaxValid(propName, entityType))
		{
			out_propertyGroup.simpleProperties.emplace_back(std::move(propName), (*it));

			return true;
		}
	}

	_parsingErrorDescription = "Invalid simple property: " + std::move(propName);

	return false;
}

bool PropertyParser::addComplexProperty(std::vector<std::string>& propertyAsVector, EntityInfo::EType entityType, PropertyGroup& out_propertyGroup) noexcept
{
	std::string mainProp = std::move(propertyAsVector[0]);

	//Search the first complex property rule matching with the given mainProp and entity type
	//Iterate backwards because native properties are at the end and a user rule should never override a native rule
	for (decltype(_propertyParsingSettings->complexPropertyRules)::const_reverse_iterator it = _propertyParsingSettings->complexPropertyRules.crbegin(); it != _propertyParsingSettings->complexPropertyRules.crend(); it++)
	{
		if ((*it)->isMainPropSyntaxValid(mainProp, entityType))
		{
			//Found a matching property rule

			ComplexProperty	complexProp(std::move(mainProp), (*it));
			std::string		subProp;

			//Check syntax validity of each subproperty
			for (uint8 i = 1u; i < propertyAsVector.size(); i++)
			{
				subProp = std::move(propertyAsVector[i]);

				if ((*it)->isSubPropSyntaxValid(subProp, i - 1u, _parsingErrorDescription))	// - 1 so that first subprop has index 0
				{
					complexProp.subProperties.emplace_back(std::move(subProp));
				}
				else if (subProp.empty() && propertyAsVector.size() == 2)
				{
					//If there is a single empty subprop, means there is no subprop at all
				}
				else
				{
					return false;
				}
			}

			out_propertyGroup.complexProperties.emplace_back(std::move(complexProp));

			return true;
		}
	}

	_parsingErrorDescription = "Invalid complex main property: " + std::move(mainProp);

	return false;
}

void PropertyParser::setup(PropertyParsingSettings const& propertyParsingSettings) noexcept
{
	_propertyParsingSettings = &propertyParsingSettings;

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
	_parsingErrorDescription.clear();
}

std::string const& PropertyParser::getParsingErrorDescription() const noexcept
{
	return _parsingErrorDescription;
}