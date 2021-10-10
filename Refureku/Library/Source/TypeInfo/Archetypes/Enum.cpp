#include "Refureku/TypeInfo/Archetypes/Enum.h"

#include <cstring> //std::strcmp

#include "Refureku/TypeInfo/Archetypes/EnumImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

Enum::Enum(char const* name, std::size_t id, Archetype const* underlyingArchetype, Entity const* outerEntity) noexcept:
	Archetype(new EnumImpl(name, id, underlyingArchetype, outerEntity))
{
}

Enum::~Enum() noexcept = default;

EnumValue* Enum::addEnumValue(char const* name, std::size_t id, int64 value) noexcept
{
	return &reinterpret_cast<EnumImpl*>(getPimpl())->addEnumValue(name, id, value, this);
}

void Enum::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<EnumImpl*>(getPimpl())->setEnumValuesCapacity(capacity);
}

EnumValue const* Enum::getEnumValueByName(char const* name) const noexcept
{
	for (EnumValue const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (std::strcmp(enumValue.getName(), name) == 0)
		{
			return &enumValue;
		}
	}

	return nullptr;
}

EnumValue const* Enum::getEnumValue(int64 value) const noexcept
{
	for (EnumValue const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (enumValue.getValue() == value)
		{
			return &enumValue;
		}
	}

	return nullptr;
}

EnumValue const* Enum::getEnumValueByPredicate(Predicate<EnumValue> predicate, void* userData) const
{
	for (EnumValue const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (predicate(enumValue, userData))
		{
			return &enumValue;
		}
	}

	return nullptr;
}

Vector<EnumValue const*> Enum::getEnumValues(int64 value) const noexcept
{
	Vector<EnumValue const*> result;

	for (EnumValue const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (enumValue.getValue() == value)
		{
			result.push_back(&enumValue);
		}
	}

	return result;
}

Vector<EnumValue const*> Enum::getEnumValuesByPredicate(Predicate<EnumValue> predicate, void* userData) const
{
	Vector<EnumValue const*> result;

	for (EnumValue const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (predicate(enumValue, userData))
		{
			result.push_back(&enumValue);
		}
	}

	return result;
}

EnumValue const& Enum::getEnumValueAt(std::size_t valueIndex)	const noexcept
{
	return reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues()[valueIndex];
}

std::size_t Enum::getEnumValuesCount() const noexcept
{
	return reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues().size();
}

Archetype const& Enum::getUnderlyingArchetype() const noexcept
{
	return reinterpret_cast<EnumImpl const*>(getPimpl())->getUnderlyingArchetype();
}

bool Enum::foreachEnumValue(Predicate<EnumValue> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues(), visitor, userData);
}