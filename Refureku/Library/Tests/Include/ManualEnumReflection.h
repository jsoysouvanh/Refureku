/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cstdint>	//uint8_t

//Third party enum
enum class EManualEnumReflection : uint8_t
{
	Value1 = 1 << 0,
	Value2 = 1 << 1
};

#include <Refureku/TypeInfo/Archetypes/Enum.h>

namespace rfk
{
	template <>
	rfk::Enum const* getEnum<EManualEnumReflection>() noexcept;
}