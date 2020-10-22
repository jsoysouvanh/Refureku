#pragma once

#include <Refureku/Refureku.h>
#include "ThirdPartyEnum.h"

namespace rfk
{
	template <>
	rfk::Enum const* getEnum<ThirdPartyEnum>() noexcept;
}