#pragma once

#include <Refureku/TypeInfo/Properties/PropertySettings.h>

#include "Generated/Test.rfkh.h"

constexpr rfk::EEntityKind all = (rfk::EEntityKind)~0; 

struct RFKStruct(PropertySettings(all))
	TestProperty : public rfk::Property
{
	TestProperty_GENERATED
};

struct RFKStruct(PropertySettings(all, false, false))
    TestProperty2 : public rfk::Property
{
    TestProperty2_GENERATED 
};

struct RFKStruct(PropertySettings(all))
    TestProperty3 : public rfk::Property
{
    TestProperty3_GENERATED
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

File_Test_GENERATED