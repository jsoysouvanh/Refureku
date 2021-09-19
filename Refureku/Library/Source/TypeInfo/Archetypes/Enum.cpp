#include "Refureku/TypeInfo/Archetypes/Enum.h"

#include "Refureku/TypeInfo/Type.h"

using namespace rfk;

Enum::Enum(std::string&& name, std::size_t id, uint64 memorySize, Type const& underlyingType, Entity const* outerEntity) noexcept:
	Archetype(std::forward<std::string>(name), id, EEntityKind::Enum, memorySize, outerEntity),
	underlyingType{underlyingType}
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

EnumValue* Enum::addEnumValue(std::string enumValueName, uint64 entityId, int64 value) noexcept
{
	//Add the enum value to the container
	return const_cast<EnumValue*>(&*values.emplace(std::move(enumValueName), entityId, value, this).first);
}