#include "ThirdPartyEnumReflectionCode.h"

//Register the enum to the database
rfk::ArchetypeRegisterer NonReflectedEnumRegisterer = rfk::getEnum<ThirdPartyEnum>();

template <>
rfk::Enum const* rfk::getEnum<ThirdPartyEnum>() noexcept
{
	static bool			initialized = false;
	static rfk::Enum	type("ThirdPartyEnum", std::hash<std::string>()("ThirdPartyEnum"), sizeof(ThirdPartyEnum), rfk::Type::getType<uint16_t>());

	if (!initialized)
	{
		initialized = true;

		type.values.reserve(2);

		const_cast<rfk::EnumValue&>(*type.values.emplace("Value1", std::hash<std::string>()("ThirdPartyEnum@Value1"), 0u).first).outerEntity = &type;
		const_cast<rfk::EnumValue&>(*type.values.emplace("Value2", std::hash<std::string>()("ThirdPartyEnum@Value2"), 2u).first).outerEntity = &type;
	}

	return &type;
}