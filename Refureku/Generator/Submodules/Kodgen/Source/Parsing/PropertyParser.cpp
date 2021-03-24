#include "Kodgen/Parsing/PropertyParser.h"

#include <cassert>

#include "Kodgen/Properties/SimpleProperty.h"
#include "Kodgen/Properties/ComplexProperty.h"

using namespace kodgen;

opt::optional<PropertyGroup> PropertyParser::getProperties(std::string&& annotateMessage, std::string const& annotationId, EEntityType entityType) noexcept
{
	if (annotateMessage.substr(0, annotationId.size()) == annotationId)
	{
		if (splitProperties(annotateMessage.substr(annotationId.size())))
		{
			PropertyGroup				propertyGroup	= checkAndFillPropertyGroup(_splitProps, entityType);
			SimplePropertyRule const*	propertyRule	= nullptr;

			//Check each property validity
			for (uint8 i = 0u; i < propertyGroup.simpleProperties.size(); i++)
			{
				propertyRule = propertyGroup.simpleProperties[i].boundPropertyRule;

				//If the property group is not valid, unbind the property rule
				if (propertyRule != nullptr && !propertyRule->isPropertyGroupValid(propertyGroup, i, _parsingErrorDescription))
				{
					propertyGroup.simpleProperties[i].boundPropertyRule = nullptr;
				}
			}

			for (uint8 i = 0u; i < propertyGroup.complexProperties.size(); i++)
			{
				propertyRule = propertyGroup.complexProperties[i].boundPropertyRule;

				//If the property group is not valid, unbind the property rule
				if (propertyRule != nullptr && !propertyRule->isPropertyGroupValid(propertyGroup, i, _parsingErrorDescription))
				{
					propertyGroup.complexProperties[i].boundPropertyRule = nullptr;
				}
			}

			return propertyGroup;
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

	return getProperties(std::move(annotateMessage), namespaceAnnotation, EEntityType::Namespace);
}

opt::optional<PropertyGroup> PropertyParser::getClassProperties(std::string annotateMessage) noexcept
{
	static std::string classAnnotation = "KGC:";

	return getProperties(std::move(annotateMessage), classAnnotation, EEntityType::Class);
}

opt::optional<PropertyGroup> PropertyParser::getStructProperties(std::string annotateMessage) noexcept
{
	static std::string structAnnotation = "KGS:";

	return getProperties(std::move(annotateMessage), structAnnotation, EEntityType::Struct);
}

opt::optional<PropertyGroup> PropertyParser::getVariableProperties(std::string annotateMessage) noexcept
{
	static std::string variableAnnotation = "KGV:";

	return getProperties(std::move(annotateMessage), variableAnnotation, EEntityType::Variable);
}

opt::optional<PropertyGroup> PropertyParser::getFieldProperties(std::string annotateMessage) noexcept
{
	static std::string fieldAnnotation = "KGF:";

	return getProperties(std::move(annotateMessage), fieldAnnotation, EEntityType::Field);
}

opt::optional<PropertyGroup> PropertyParser::getFunctionProperties(std::string annotateMessage) noexcept
{
	static std::string functionAnnotation = "KGFu:";

	return getProperties(std::move(annotateMessage), functionAnnotation, EEntityType::Function);
}

opt::optional<PropertyGroup> PropertyParser::getMethodProperties(std::string annotateMessage) noexcept
{
	static std::string methodAnnotation = "KGM:";

	return getProperties(std::move(annotateMessage), methodAnnotation, EEntityType::Method);
}

opt::optional<PropertyGroup> PropertyParser::getEnumProperties(std::string annotateMessage) noexcept
{
	static std::string enumAnnotation = "KGE:";

	return getProperties(std::move(annotateMessage), enumAnnotation, EEntityType::Enum);
}

opt::optional<PropertyGroup> PropertyParser::getEnumValueProperties(std::string annotateMessage) noexcept
{
	static std::string enumValueAnnotation = "KGEV:";

	return getProperties(std::move(annotateMessage), enumValueAnnotation, EEntityType::EnumValue);
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

	//Remove start and trail spaces from the added property
	removeStartSpaces(_splitProps.back().front());
	removeTrailSpaces(_splitProps.back().front());

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

		//Remove start and trail spaces from the added sub property
		removeStartSpaces(_splitProps.back().back());
		removeTrailSpaces(_splitProps.back().back());

		inout_parsingProps.erase(0, index + 1);
	}
	else	//_propertyParsingSettings->subPropertyEnclosers[1]
	{
		out_isParsingSubProp = false;

		_splitProps.back().push_back(std::string(inout_parsingProps.cbegin(), inout_parsingProps.cbegin() + index));

		//Remove start and trail spaces from the added sub property
		removeStartSpaces(_splitProps.back().back());
		removeTrailSpaces(_splitProps.back().back());

		//Make sure there is a property separator after the end encloser if is not the last char of the string
		if (index != inout_parsingProps.size() - 1)
		{
			size_t propSeparatorIndex = inout_parsingProps.find_first_not_of(' ', index + 1);

			if (inout_parsingProps[propSeparatorIndex] != _propertyParsingSettings->propertySeparator)
			{
				_parsingErrorDescription = "Property separator \"" + std::string(1, _propertyParsingSettings->propertySeparator) + "\" is missing between two properties.";

				return false;
			}
			else
			{
				inout_parsingProps.erase(0, propSeparatorIndex + 1); // + 1 to consume prop separator
			}
		}
		else
		{
			//index is the last character, so consume the rest of the string
			inout_parsingProps.clear();
		}
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

void PropertyParser::removeStartSpaces(std::string& toCleanString) const noexcept
{
	toCleanString.erase(0, toCleanString.find_first_not_of(' '));
}

void PropertyParser::removeTrailSpaces(std::string& toCleanString) const noexcept
{
	toCleanString.erase(toCleanString.find_last_not_of(' ') + 1);
}

PropertyGroup PropertyParser::checkAndFillPropertyGroup(std::vector<std::vector<std::string>>& splitProps, EEntityType entityType) noexcept
{
	PropertyGroup propertyGroup;

	for (std::vector<std::string>& props : splitProps)
	{
		//Expect a simple prop
		if (props.size() == 1u)
		{
			addSimpleProperty(props, entityType, propertyGroup);
		}
		//Expect a complex prop
		else
		{
			addComplexProperty(props, entityType, propertyGroup);
		}
	}

	return propertyGroup;
}

void PropertyParser::addSimpleProperty(std::vector<std::string>& propertyAsVector, EEntityType entityType, PropertyGroup& out_propertyGroup) noexcept
{
	std::string propName = std::move(propertyAsVector[0]);

	//Search the first simple property rule matching with the given name and entity type
	//Iterate backwards because native properties are at the end and a user rule should never override a native rule
	for (decltype(_propertyParsingSettings->simplePropertyRules)::const_reverse_iterator it = _propertyParsingSettings->simplePropertyRules.crbegin(); it != _propertyParsingSettings->simplePropertyRules.crend(); it++)
	{
		if ((*it)->isMainPropSyntaxValid(propName, entityType))
		{
			out_propertyGroup.simpleProperties.emplace_back(std::move(propName), *it);

			return;
		}
	}

	out_propertyGroup.simpleProperties.emplace_back(std::move(propName), nullptr);
}

void PropertyParser::addComplexProperty(std::vector<std::string>& propertyAsVector, EEntityType entityType, PropertyGroup& out_propertyGroup) noexcept
{
	assert(propertyAsVector.size() >= 2);

	ComplexProperty	complexProp(std::move(propertyAsVector[0]), nullptr);
	std::string		subProp;

	//Add all subproperties to the complex property
	//If propertyAsVector has 2 elements and the 2nd element is empty, there are no subprops
	if (propertyAsVector.size() != 2 || !propertyAsVector[1].empty())
		complexProp.subProperties.insert(complexProp.subProperties.cend(), std::make_move_iterator(propertyAsVector.begin() + 1), std::make_move_iterator(propertyAsVector.end()));

	//Search the first complex property rule matching with the given mainProp and entity type
	//Iterate backwards because native properties are at the end and a user rule should never override a native rule
	for (decltype(_propertyParsingSettings->complexPropertyRules)::const_reverse_iterator it = _propertyParsingSettings->complexPropertyRules.crbegin(); it != _propertyParsingSettings->complexPropertyRules.crend(); it++)
	{
		if ((*it)->isMainPropSyntaxValid(complexProp.mainProperty, entityType))
		{
			//Found a matching property rule
			complexProp.boundPropertyRule = *it;

			//Check syntax validity of each subproperty
			for (uint8 i = 0u; i < complexProp.subProperties.size(); i++)
			{
				subProp = complexProp.subProperties[i];

				if (!(*it)->isSubPropSyntaxValid(subProp, i, _parsingErrorDescription))
				{
					//The subproperty doesn't match the native property
					complexProp.boundPropertyRule = nullptr;
	
					break;
				}
			}

			//If there is still a bound property at this point, all subproperties were valid
			if (complexProp.boundPropertyRule != nullptr)
			{
				break;
			}
		}
	}

	out_propertyGroup.complexProperties.emplace_back(std::move(complexProp));
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