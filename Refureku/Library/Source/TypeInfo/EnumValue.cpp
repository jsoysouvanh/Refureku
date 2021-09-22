#include "Refureku/TypeInfo/Archetypes/EnumValue.h"

using namespace rfk;

EnumValue::EnumValue(std::string&& name, std::size_t id, int64 value, Entity const* outerEntity) noexcept:
	Entity(std::forward<std::string>(name), id, EEntityKind::EnumValue, outerEntity),
	_value{value}
{
}