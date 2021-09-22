#include "ThirdPartyEnumReflectionCode.h"

#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Type.h>

//Register the enum to the database
rfk::ArchetypeRegisterer NonReflectedEnumRegisterer = *rfk::getEnum<ThirdPartyEnum>();

template <>
rfk::Enum const* rfk::getEnum<ThirdPartyEnum>() noexcept
{
	static bool			initialized = false;
	static rfk::Enum	type("ThirdPartyEnum", std::hash<std::string>()("ThirdPartyEnum"), sizeof(ThirdPartyEnum), rfk::getArchetype<uint16_t>());

	if (!initialized)
	{
		initialized = true;

		type.setEnumValuesCapacity(2);
		type.addEnumValue("Value1", std::hash<std::string>()("ThirdPartyEnum@Value1"), 0u);
		type.addEnumValue("Value2", std::hash<std::string>()("ThirdPartyEnum@Value2"), 2u);
	}

	return &type;
}