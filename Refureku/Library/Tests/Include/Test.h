#pragma once

#include <Refureku/TypeInfo/Properties/PropertySettings.h>

constexpr rfk::EEntityKind all = (rfk::EEntityKind)~0;

#include "Generated/Test.rfk.h"

//struct RFKStruct(PropertySettings(rfk::EEntityKind::Namespace)) TestProperty : public rfk::Property
//{
//	TestProperty_GENERATED
//};

struct RFKStruct(PropertySettings(all))
	TestProperty : public rfk::Property
{
	TestProperty_GENERATED
};

//struct RFKStruct(PropertySettings(rfk::EEntityKind::Class)) TestProperty : public rfk::Property
//{
//	TestProperty_GENERATED
//};

File_GENERATED