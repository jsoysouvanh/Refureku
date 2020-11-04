#pragma once

#include <Refureku/NativeProperties.h>

#include "Generated/CustomProperties.rfk.h"

struct RFKStruct(PropertySettings(rfk::EEntityKind::Field | rfk::EEntityKind::Class, true, true)) CustomProperty : public rfk::Property
{
	RFKField()
	int i = 0;

	RFKField()
	int j = 0;

	CustomProperty() = default;
	CustomProperty(int _i, int _j) noexcept: i{_i}, j{_j} {}

	CustomProperty_GENERATED
};

struct RFKStruct(PropertySettings(rfk::EEntityKind::Class, true, true)) CustomProperty2 : public CustomProperty
{
	CustomProperty2_GENERATED 
};

File_GENERATED