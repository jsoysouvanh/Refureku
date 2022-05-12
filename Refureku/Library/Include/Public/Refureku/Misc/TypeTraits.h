/**
*	Copyright (c) 2020-2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Misc/TypeTraitsMacros.h"

namespace rfk::internal
{
	RFK_GENERATE_IS_CALLABLE_METHOD_TRAITS(getArchetype);
	RFK_GENERATE_IS_CALLABLE_STATIC_METHOD_TRAITS(staticGetArchetype);
}