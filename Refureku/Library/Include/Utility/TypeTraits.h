#pragma once

#include "Utility/TypeTraitsMacros.h"

#include "TypeInfo/Archetypes/ArchetypeRegisterer.h"

namespace rfk
{
	GENERATE_HAS_FIELD_TRAITS(__rfkArchetypeRegisterer)

	template <typename T>
	static constexpr bool isReflectedClass = std::is_class_v<T> && hasField___rfkArchetypeRegisterer<T, rfk::ArchetypeRegisterer>::value;
}