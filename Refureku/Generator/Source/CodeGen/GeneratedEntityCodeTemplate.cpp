#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

#include <cassert>
#include <algorithm>	//std::remove

#include <Kodgen/Properties/SimplePropertyRule.h>
#include <Kodgen/Properties/ComplexPropertyRule.h>

#include "RefurekuGenerator/Properties/PropertyCodeGenData.h"

using namespace rfk;

std::hash<std::string> const GeneratedEntityCodeTemplate::stringHasher;

std::string GeneratedEntityCodeTemplate::fillEntityProperties(kodgen::EntityInfo const& info, std::string const& entityVarName) const noexcept
{
	std::string			result;
	std::string			propVarName;
	size_t				propsCount	= info.properties.simpleProperties.size() + info.properties.complexProperties.size();
	kodgen::uint8		index		= 0u;
	PropertyCodeGenData	data{ECodeGenLocation::PropertyAdd};

	if (propsCount > 0)
	{
		//Keep track of all added properties, propName -> count
		std::unordered_map<std::string, uint8_t> propertiesRecord;

		//Reserve space to avoid reallocation
		result += entityVarName + "properties.reserve(" + std::to_string(propsCount) + ");";

		//Add simple props
		for (kodgen::SimpleProperty const& prop : info.properties.simpleProperties)
		{
			//Generate property relative code
			if (prop.boundPropertyRule != nullptr)
				result += prop.boundPropertyRule->generateCode(info, prop, &data);

			result += addSimplePropertyToEntity(info, entityVarName, prop.mainProperty, index, addToPropertiesRecord(propertiesRecord, prop.mainProperty) > 1u);

			index++;
		}

		//Add complex props
		for (kodgen::ComplexProperty const& prop : info.properties.complexProperties)
		{
			//Generate property relative code
			if (prop.boundPropertyRule != nullptr)
				result += prop.boundPropertyRule->generateCode(info, prop, &data);

			if (prop.subProperties.empty())
			{
				result += addSimplePropertyToEntity(info, entityVarName, prop.mainProperty, index, addToPropertiesRecord(propertiesRecord, prop.mainProperty) > 1u);
			}
			else
			{
				result += addComplexPropertyToEntity(info, entityVarName, prop, index, addToPropertiesRecord(propertiesRecord, prop.mainProperty) > 1u);
			}

			index++;
		}
	}

	return result;
}

uint8_t GeneratedEntityCodeTemplate::addToPropertiesRecord(std::unordered_map<std::string, uint8_t>& record, std::string const& propName) const noexcept
{
	std::unordered_map<std::string, uint8_t>::iterator it = record.find(propName);

	if (it != record.end())
	{
		return ++it->second;
	}
	else
	{
		//static_cast to get rid of warning
		record.emplace(propName, static_cast<uint8_t>(1u));

		return 1u;
	}
}

std::string GeneratedEntityCodeTemplate::getRefurekuEntityKind(kodgen::EEntityType entityType) const noexcept
{
	switch (entityType)
	{
		case kodgen::EEntityType::Struct:
			return "rfk::EEntityKind::Struct";

		case kodgen::EEntityType::Class:
			return "rfk::EEntityKind::Class";

		case kodgen::EEntityType::Enum:
			return "rfk::EEntityKind::Enum";

		case kodgen::EEntityType::EnumValue:
			return "rfk::EEntityKind::EnumValue";

		case kodgen::EEntityType::Field:
			return "rfk::EEntityKind::Field";

		case kodgen::EEntityType::Method:
			return "rfk::EEntityKind::Method";

		case kodgen::EEntityType::Variable:
			return "rfk::EEntityKind::Variable";

		case kodgen::EEntityType::Function:
			return "rfk::EEntityKind::Function";

		case kodgen::EEntityType::Namespace:
			return "rfk::EEntityKind::Namespace";

		case kodgen::EEntityType::Undefined:
			return "rfk::EEntityKind::Undefined";
			break;
	}

	//Should never reach this point
	assert(false);
	
	return "";
}

std::string GeneratedEntityCodeTemplate::getEntityKindName(kodgen::EEntityType entityType) const noexcept
{
	switch (entityType)
	{
		case kodgen::EEntityType::Struct:
			return "struct";

		case kodgen::EEntityType::Class:
			return "class";

		case kodgen::EEntityType::Enum:
			return "enum";

		case kodgen::EEntityType::EnumValue:
			return "enum value";

		case kodgen::EEntityType::Field:
			return "field";

		case kodgen::EEntityType::Method:
			return "method";

		case kodgen::EEntityType::Variable:
			return "variable";

		case kodgen::EEntityType::Function:
			return "function";

		case kodgen::EEntityType::Namespace:
			return "namespace";

		case kodgen::EEntityType::Undefined:
			break;
	}

	//Should never reach this point
	assert(false);

	return "";
}

std::string GeneratedEntityCodeTemplate::generatePropertyVariableName(kodgen::EntityInfo const& info, std::string propName, kodgen::uint8 propIndex) const noexcept
{
	//Remove spaces from the property name
	propName.erase(std::remove(propName.begin(), propName.end(), ' '), propName.end());

	return "property_" + info.name + "_" + std::move(propName) + "_" + std::to_string(propIndex) + "_" + std::to_string(stringHasher(info.id));
}

std::string GeneratedEntityCodeTemplate::generateStaticAsserts(kodgen::EntityInfo const& info, std::string const& propName, bool generateTargetEntityKindAssert, bool generateAllowMultipleAssert) const noexcept
{
	std::string result;

	if (generateTargetEntityKindAssert)
	{
		result += generatePropertyTargetEntityKindAssert(info, propName);
	}

	if (generateAllowMultipleAssert)
	{
		result += generatePropertyAllowMultipleAssert(info, propName);
	}

	return result;
}

std::string GeneratedEntityCodeTemplate::generatePropertyTargetEntityKindAssert(kodgen::EntityInfo const& info, std::string const& propName) const noexcept
{
	return	"static_assert((" + propName + "::targetEntityKind & " + getRefurekuEntityKind(info.entityType) + ") != " + getRefurekuEntityKind(kodgen::EEntityType::Undefined) +
			", \"[Refureku] " + propName + " can't be applied to a " + getEntityKindName(info.entityType) + "\");";
}

std::string GeneratedEntityCodeTemplate::generatePropertyAllowMultipleAssert(kodgen::EntityInfo const& info, std::string const& propName) const noexcept
{
	return "static_assert(" + propName + "::allowMultiple, \"[Refureku] " + info.getFullName() + ": " + propName + " can't be attached multiple times to a single entity.\");";
}

std::string GeneratedEntityCodeTemplate::addSimplePropertyToEntity(kodgen::EntityInfo const& info, std::string const& entityVarName, std::string const& propName, kodgen::uint8 propIndex, bool generateAllowMultipleAssert) const noexcept
{
	std::string propVarName = generatePropertyVariableName(info, propName, propIndex);
	std::string result;

	//Generate static_asserts relative to this entity/property
	result += generateStaticAsserts(info, propName, true, generateAllowMultipleAssert);

	result += "static " + propName + " " + propVarName + "; " + entityVarName + "properties.emplace_back(&" + propVarName + "); ";

	return result;
}

std::string GeneratedEntityCodeTemplate::addComplexPropertyToEntity(kodgen::EntityInfo const& info, std::string const& entityVarName, kodgen::ComplexProperty const& prop, kodgen::uint8 propIndex, bool generateAllowMultipleAssert) const noexcept
{
	assert(!prop.subProperties.empty());

	std::string propVarName = generatePropertyVariableName(info, prop.mainProperty, propIndex);
	std::string result;
	
	//Generate static_asserts relative to this entity/property
	result += generateStaticAsserts(info, prop.mainProperty, true, generateAllowMultipleAssert);

	result += "static " + prop.mainProperty + " " + propVarName + "{";

	for (std::string subProp : prop.subProperties)
	{
		result += subProp + ",";
	}

	//Replace last , by closing }
	result.back() = '}';

	result.push_back(';');

	result += entityVarName + "properties.emplace_back(&" + propVarName + "); ";

	return result;
}

std::string GeneratedEntityCodeTemplate::generateNativePropertiesCode(kodgen::EntityInfo const& entityInfo, void* propCodeGenData) noexcept
{
	std::string result;

	for (kodgen::SimpleProperty const& prop : entityInfo.properties.simpleProperties)
	{
		if (prop.boundPropertyRule != nullptr)
		{
			result += prop.boundPropertyRule->generateCode(entityInfo, prop, propCodeGenData);
		}
	}

	for (kodgen::ComplexProperty const& prop : entityInfo.properties.complexProperties)
	{
		if (prop.boundPropertyRule != nullptr)
		{
			result += prop.boundPropertyRule->generateCode(entityInfo, prop, propCodeGenData);
		}
	}

	return result;
}