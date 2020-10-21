#pragma once

#include <Refureku/Refureku.h>
#include "ThirdPartyEnum.h"

namespace rfk
{
	template <>
	inline rfk::Enum const* getEnum<ThirdPartyEnum>() noexcept;
}