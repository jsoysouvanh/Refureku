#include "TypeInfo/Archetypes/Enum.h"

using namespace rfk;

Enum::Enum(std::string&& name, uint64 id, uint64 memorySize) noexcept:
	Archetype(std::forward<std::string>(name), id, ECategory::Enum, memorySize)
{
}

EnumValue const* Enum::getEnumValue(std::string enumValueName)  const noexcept
{
	decltype(values)::const_iterator it = values.find(static_cast<EnumValue&&>(Entity(std::move(enumValueName), 0u)));

	return (it != values.cend()) ? &*it : nullptr;
}

EnumValue const* Enum::getEnumValue(int64 value) const noexcept
{
	decltype(values)::const_iterator it = std::find_if(values.cbegin(), values.cend(), [value](EnumValue const& v)
													   { return v.value == value; });

	return (it != values.cend()) ? &*it : nullptr;
}

std::vector<EnumValue const*> Enum::getEnumValues(int64 value) const noexcept
{
	std::vector<EnumValue const*> result;

	for (EnumValue const& ev : values)
	{
		if (ev.value == value)
		{
			result.push_back(&ev);
		}
	}

	return result;
}