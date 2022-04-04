/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Properties/Property.h"
#include "Refureku/Properties/PropertySettings.h"

#include "Refureku/Generated/Instantiator.rfkh.h"

namespace rfk RFKNamespace()
{
	/**
	*	@brief	Property used to add a new instantiator to a struct or class through the rfk::Struct::makeSharedInstance method.
	*			This property can only be attached to static methods returning a shared pointer to the class (rfk::SharedPtr<YourClass>).
	*/
	class REFUREKU_API RFKClass(rfk::PropertySettings(rfk::EEntityKind::Method)) Instantiator : public rfk::Property
	{
		rfk_Instantiator_GENERATED
	};
}

File_Instantiator_GENERATED