#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"

#include <cstring> //std::strcmp

#include "Refureku/TypeInfo/Archetypes/EnumImpl.h"

using namespace rfk;

EnumAPI::EnumAPI(char const* name, std::size_t id, ArchetypeAPI const* underlyingArchetype, EntityAPI const* outerEntity) noexcept:
	ArchetypeAPI(new EnumImpl(name, id, underlyingArchetype, outerEntity))
{
}

EnumAPI::~EnumAPI() noexcept = default;

EnumValueAPI* EnumAPI::addEnumValue(char const* name, std::size_t id, int64 value) noexcept
{
	return &reinterpret_cast<EnumImpl*>(getPimpl())->addEnumValue(name, id, value, this);
}

void EnumAPI::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<EnumImpl*>(getPimpl())->setEnumValuesCapacity(capacity);
}

EnumValueAPI const* EnumAPI::getEnumValueByName(char const* name) const noexcept
{
	for (EnumValueAPI const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (std::strcmp(enumValue.getName(), name) == 0)
		{
			return &enumValue;
		}
	}

	return nullptr;
}

EnumValueAPI const* EnumAPI::getEnumValue(int64 value) const noexcept
{
	for (EnumValueAPI const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (enumValue.getValue() == value)
		{
			return &enumValue;
		}
	}

	return nullptr;
}

EnumValueAPI const* EnumAPI::getEnumValueByPredicate(EnumValuePredicate predicate, void* userData) const noexcept
{
	for (EnumValueAPI const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (predicate(enumValue, userData))
		{
			return &enumValue;
		}
	}

	return nullptr;
}

Vector<EnumValueAPI const*> EnumAPI::getEnumValues(int64 value) const noexcept
{
	Vector<EnumValueAPI const*> result;

	for (EnumValueAPI const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (enumValue.getValue() == value)
		{
			result.push_back(&enumValue);
		}
	}

	return result;
}

Vector<EnumValueAPI const*> EnumAPI::getEnumValuesByPredicate(EnumValuePredicate predicate, void* userData) const noexcept
{
	Vector<EnumValueAPI const*> result;

	for (EnumValueAPI const& enumValue : reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues())
	{
		if (predicate(enumValue, userData))
		{
			result.push_back(&enumValue);
		}
	}

	return result;
}

EnumValueAPI const& EnumAPI::getEnumValueAt(std::size_t valueIndex)	const noexcept
{
	return reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues()[valueIndex];
}

std::size_t EnumAPI::getEnumValuesCount() const noexcept
{
	return reinterpret_cast<EnumImpl const*>(getPimpl())->getEnumValues().size();
}

ArchetypeAPI const& EnumAPI::getUnderlyingArchetype() const noexcept
{
	return reinterpret_cast<EnumImpl const*>(getPimpl())->getUnderlyingArchetype();
}