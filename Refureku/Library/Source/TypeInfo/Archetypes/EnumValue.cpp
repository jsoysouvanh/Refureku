#include "Refureku/TypeInfo/Archetypes/EnumValue.h"

#include "Refureku/TypeInfo/Archetypes/EnumValueImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<EnumValue const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<EnumValue const*, rfk::Allocator<EnumValue const*>>;

EnumValue::EnumValue(char const* name, std::size_t id, int64 value, Entity const* outerEntity) noexcept:
	Entity(new EnumValueImpl(name, id, value, outerEntity))
{
}

EnumValue::EnumValue(EnumValue&& other) noexcept = default;

EnumValue::~EnumValue() noexcept = default;

int64 EnumValue::getValue() const noexcept
{
	return getPimpl()->getValue();
}