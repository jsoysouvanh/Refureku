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
	return (name != nullptr) ? &getPimpl()->addEnumValue(name, id, value, this) : nullptr;
}

void Enum::setEnumValuesCapacity(std::size_t capacity) noexcept
{
	getPimpl()->setEnumValuesCapacity(capacity);
}

EnumValue const* Enum::getEnumValueByName(char const* name) const noexcept
{
	return (name != nullptr) ? EntityUtility::getEntityByPredicate(getPimpl()->getEnumValues(), [name](EnumValue const& ev)
											   {
												   return std::strcmp(ev.getName(), name) == 0;
											   }) : nullptr;
}

EnumValue const* Enum::getEnumValue(int64 value) const noexcept
{
	return EntityUtility::getEntityByPredicate(getPimpl()->getEnumValues(), [value](EnumValue const& ev)
											   {
												   return ev.getValue() == value;
											   });
}

EnumValue const* Enum::getEnumValueByPredicate(Predicate<EnumValue> predicate, void* userData) const
{
	return EntityUtility::getEntityByPredicate(getPimpl()->getEnumValues(), predicate, userData);
}

Vector<EnumValue const*> Enum::getEnumValues(int64 value) const noexcept
{
	return EntityUtility::getEntitiesByPredicate(getPimpl()->getEnumValues(), [value](EnumValue const& ev)
												 {
													 return ev.getValue() == value;
												 });
}

Vector<EnumValue const*> Enum::getEnumValuesByPredicate(Predicate<EnumValue> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(getPimpl()->getEnumValues(), predicate, userData);
}

EnumValue const& Enum::getEnumValueAt(std::size_t valueIndex)	const noexcept
{
	return getPimpl()->getEnumValues()[valueIndex];
}

std::size_t Enum::getEnumValuesCount() const noexcept
{
	return getPimpl()->getEnumValues().size();
}

Archetype const& Enum::getUnderlyingArchetype() const noexcept
{
	return getPimpl()->getUnderlyingArchetype();
}

bool Enum::foreachEnumValue(Predicate<EnumValue> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(getPimpl()->getEnumValues(), visitor, userData);
}