/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"

#if defined(REFUREKU_EXPORT)

#include "Refureku/Misc/GetPimplMacroImpl.h"

#else

#define RFK_GEN_GET_PIMPL(type, source)

#endif