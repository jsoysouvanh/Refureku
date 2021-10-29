/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"

#define RFK_GEN_GET_PIMPL(type, source) \
    RFK_NODISCARD inline type* getPimpl() noexcept { return reinterpret_cast<type*>(source); } \
    RFK_NODISCARD inline type const* getPimpl() const noexcept { return reinterpret_cast<type const*>(source); }

