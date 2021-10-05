#include "ThirdPartyEnumReflectionCode.h"

#include <string_view>

#include <Refureku/TypeInfo/Archetypes/ArchetypeRegistererAPI.h>
#include <Refureku/TypeInfo/TypeAPI.h>

//Register the enum to the database
rfk::ArchetypeRegistererAPI NonReflectedEnumRegisterer = *rfk::getEnumAPI<ThirdPartyEnum>();

template <>
rfk::EnumAPI const* rfk::getEnumAPI<ThirdPartyEnum>() noexcept
{
	static bool			initialized = false;
	static rfk::EnumAPI	type("ThirdPartyEnum", std::hash<std::string_view>()("ThirdPartyEnum"), rfk::getArchetypeAPI<uint16_t>());

	if (!initialized)
	{
		initialized = true;

		type.setEnumValuesCapacity(2);
		type.addEnumValue("Value1", std::hash<std::string_view>()("ThirdPartyEnum@Value1"), 0u);
		type.addEnumValue("Value2", std::hash<std::string_view>()("ThirdPartyEnum@Value2"), 2u);
	}

	return &type;
}