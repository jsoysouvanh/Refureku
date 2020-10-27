#include "Refureku/TypeInfo/Archetypes/EnumValue.h"

using namespace rfk;

EnumValue::EnumValue(std::string&& name, uint64 id, int64 value) noexcept:
	Entity(std::forward<std::string>(name), id, EKind::EnumValue),
	value{value}
{
}