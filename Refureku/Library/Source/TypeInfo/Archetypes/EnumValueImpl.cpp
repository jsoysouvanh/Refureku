#include "Refureku/TypeInfo/Archetypes/EnumValueImpl.h"

using namespace rfk;

EnumValueAPI::EnumValueImpl::EnumValueImpl(char const* name, std::size_t id, int64 value, EntityAPI const* outerEntity) noexcept:
	EntityImpl(name, id, EEntityKind::EnumValue, outerEntity),
	_value{value}
{
}

int64 EnumValueAPI::EnumValueImpl::getValue() const noexcept
{
	return _value;
}