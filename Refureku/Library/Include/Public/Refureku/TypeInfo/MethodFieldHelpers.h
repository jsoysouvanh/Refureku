/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/TypeTraits.h"

namespace rfk::internal
{
	template <typename T>
	constexpr bool IsAdjustableInstanceValue = internal::isCallable_static_staticGetArchetype<T, Struct const&()>::value &&
												internal::isCallable_getArchetype<T, Struct const&()>::value;

	template <typename T>
	using IsAdjustableInstance = std::enable_if_t<IsAdjustableInstanceValue<T>>;
}