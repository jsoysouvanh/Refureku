/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Properties/Property.h"
#include "Refureku/Properties/PropertySettings.h"

#include "Refureku/Generated/Instantiator.rfkh.h"

/**
*	@brief	Property used to add a new way to instantiate a struct or class through the rfk::Struct::makeInstance method.
*			This property can only be attached to static methods returning a pointer to the class.
*/
class REFUREKU_API RFKClass(PropertySettings(rfk::EEntityKind::Method)) Instantiator : public rfk::Property
{
	Instantiator_GENERATED
};

File_Instantiator_GENERATED