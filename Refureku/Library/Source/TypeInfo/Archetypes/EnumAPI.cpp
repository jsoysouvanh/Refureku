#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"

#include <cstring> //std::strcmp

#include "Refureku/TypeInfo/Archetypes/EnumImpl.h"

using namespace rfk;

EnumAPI::EnumAPI(char const* name, std::size_t id, ArchetypeAPI const* underlyingArchetype, EntityAPI const* outerEntity) noexcept:
	ArchetypeAPI(),
	_pimpl(name, id, underlyingArchetype, outerEntity)
{
	ArchetypeAPI::setImpl(_pimpl.get());
}

EnumAPI::EnumAPI(EnumAPI const& other) noexcept:
	_pimpl{other._pimpl}
{
	ArchetypeAPI::setImpl(_pimpl.get());
}

EnumAPI::EnumAPI(EnumAPI&& other) noexcept:
	_pimpl{std::forward<Pimpl<EnumImpl>>(other._pimpl)}
{
	ArchetypeAPI::setImpl(_pimpl.get());
}

EnumAPI::~EnumAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

EnumValueAPI* EnumAPI::addEnumValue(char const* name, std::size_t id, int64 value) noexcept
{
	return &_pimpl->addEnumValue(name, id, value, this);
}

void EnumAPI::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	_pimpl->setEnumValuesCapacity(capacity);
}

EnumValueAPI const* EnumAPI::getEnumValueByName(char const* name) const noexcept
{
	for (EnumValueAPI const& enumValue : _pimpl->getEnumValues())
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
	for (EnumValueAPI const& enumValue : _pimpl->getEnumValues())
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
	for (EnumValueAPI const& enumValue : _pimpl->getEnumValues())
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

	for (EnumValueAPI const& enumValue : _pimpl->getEnumValues())
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

	for (EnumValueAPI const& enumValue : _pimpl->getEnumValues())
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
	return _pimpl->getEnumValues()[valueIndex];
}

std::size_t EnumAPI::getEnumValuesCount() const noexcept
{
	return _pimpl->getEnumValues().size();
}

ArchetypeAPI const& EnumAPI::getUnderlyingArchetype() const noexcept
{
	return _pimpl->getUnderlyingArchetype();
}