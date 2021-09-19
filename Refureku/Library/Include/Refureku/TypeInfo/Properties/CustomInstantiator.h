/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Properties/Property.h"
#include "Refureku/TypeInfo/Properties/PropertySettings.h"

#include "Refureku/Generated/CustomInstantiator.rfkh.h"

/**
*	@brief	Property used to add a new way to instantiate a struct or class through the rfk::Struct::makeInstance method.
*			This property can only be attached to static methods returning a pointer to the class.
*/
struct REFUREKU_API RFKStruct(PropertySettings(rfk::EEntityKind::Method)) CustomInstantiator : public rfk::Property
{
	CustomInstantiator_GENERATED
};

File_CustomInstantiator_GENERATED