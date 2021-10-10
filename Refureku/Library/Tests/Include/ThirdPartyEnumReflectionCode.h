#pragma once

#include "ThirdPartyEnum.h"

#include <Refureku/TypeInfo/Archetypes/Enum.h>

namespace rfk
{
	template <>
	rfk::Enum const* getEnumAPI<ThirdPartyEnum>() noexcept;
}