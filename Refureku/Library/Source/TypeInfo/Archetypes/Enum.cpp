#include "Refureku/TypeInfo/Archetypes/Enum.h"

#include <cassert>

#include "Refureku/TypeInfo/Type.h"

using namespace rfk;

Enum::Enum(std::string&& name, std::size_t id, std::size_t memorySize, Archetype const* underlyingType, Entity const* outerEntity) noexcept:
	Archetype(std::forward<std::string>(name), id, EEntityKind::Enum, memorySize, outerEntity),
	_underlyingType{*underlyingType}
{
	assert(underlyingType != nullptr);
}

EnumValue const* Enum::getEnumValue(std::string enumValueName)  const noexcept
{
	for (EnumValue const& enumValue : _enumValues)
	{
		if (enumValue.getName() == enumValueName)
		{
			return &enumValue;
		}
	}
	
	return nullptr;
}

EnumValue const* Enum::getEnumValue(int64 value) const noexcept
{
	for (EnumValue const& enumValue : _enumValues)
	{
		if (enumValue.value() == value)
		{
			return &enumValue;
		}
	}

	return nullptr;
}

std::vector<EnumValue const*> Enum::getEnumValues(int64 value) const noexcept
{
	std::vector<EnumValue const*> result;

	for (EnumValue const& ev : _enumValues)
	{
		if (ev.value() == value)
		{
			result.push_back(&ev);
		}
	}

	return result;
}

EnumValue* Enum::addEnumValue(std::string enumValueName, std::size_t entityId, int64 value) noexcept
{
	return &_enumValues.emplace_back(std::move(enumValueName), entityId, value, this);
}

void Enum::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	_enumValues.reserve(capacity);
}

EnumValue const& Enum::getEnumValueAt(std::size_t valueIndex) const
{
	return _enumValues.at(valueIndex);
}

std::size_t Enum::getEnumValuesCount() const noexcept
{
	return _enumValues.size();
}

Archetype const& Enum::getUnderlyingType() const noexcept
{
	return _underlyingType;
}