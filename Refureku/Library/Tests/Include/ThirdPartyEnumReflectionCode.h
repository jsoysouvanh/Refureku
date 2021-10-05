#pragma once

#include "ThirdPartyEnum.h"

#include <Refureku/TypeInfo/Archetypes/EnumAPI.h>

namespace rfk
{
	template <>
	rfk::EnumAPI const* getEnumAPI<ThirdPartyEnum>() noexcept;
}