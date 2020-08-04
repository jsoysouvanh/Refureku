/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"
#include "Refureku/Utility/TypeTraitsMacros.h"

namespace rfk
{
	GENERATE_HAS_FIELD_TRAITS(__rfkArchetypeRegisterer)

	template <typename T>
	static constexpr bool isReflectedClass = std::is_class_v<T> && hasField___rfkArchetypeRegisterer<T, rfk::ArchetypeRegisterer>::value;
}