#pragma once

#include <Refureku/TypeInfo/Properties/PropertySettings.h>

constexpr rfk::EEntityKind all = (rfk::EEntityKind)~0;

#include "Generated/Test.rfk.h"

struct RFKStruct(PropertySettings(all))
	TestProperty : public rfk::Property
{
	TestProperty_GENERATED
};

struct RFKStruct(PropertySettings(rfk::EEntityKind::Field | rfk::EEntityKind::Variable))
    Slider : public rfk::Property
{
    float min = 0.0f;
    float max = 1.0f;

    Slider(float _min, float _max) noexcept:
        min{_min},
        max{_max}
    {}

    Slider_GENERATED
};

File_GENERATED