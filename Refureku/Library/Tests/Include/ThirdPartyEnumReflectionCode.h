#pragma once

#include "ThirdPartyEnum.h"

#include "Generated/ThirdPartyEnumReflectionCode.rfkh.h"

namespace rfk
{
	template <>
	rfk::Enum const* getEnum<ThirdPartyEnum>() noexcept;
}

File_ThirdPartyEnumReflectionCode_GENERATED