#include "ManualEnumReflection.h"

#include <string_view>	//std::hash<std::string_view>

#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>

template <>
rfk::Enum const* rfk::getEnum<EManualEnumReflection>() noexcept
{
	static bool initialized = false;
	static rfk::Enum enumArchetype("EManualEnumReflection",
								   std::hash<std::string_view>()("EManualEnumReflection"),
								   rfk::getArchetype<uint8_t>(),
								   nullptr);

	if (!initialized)
	{
		initialized = true;

		enumArchetype.addEnumValue("Value1", std::hash<std::string_view>()("Value1"), 1 << 0);
		enumArchetype.addEnumValue("Value2", std::hash<std::string_view>()("Value2"), 1 << 1);
	}
	
	return &enumArchetype;
}

rfk::ArchetypeRegisterer registerer = *rfk::getEnum<EManualEnumReflection>();