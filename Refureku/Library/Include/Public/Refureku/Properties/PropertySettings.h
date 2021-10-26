/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Properties/Property.h"

#include "Refureku/Generated/PropertySettings.rfkh.h"

namespace rfk RFKNamespace()
{
	/**
	*	@brief Property used to define basic settings of a property. Can't be used on structs or classes not inheriting from rfk::Property.
	*/
	class REFUREKU_API RFKClass(rfk::PropertySettings(rfk::EEntityKind::Struct | rfk::EEntityKind::Class)) PropertySettings : public rfk::Property
	{
		public:
		/**
		*	@param targetEntityKind_	Kind of entities the property can be attached to. Use the | operator to specify multiple entity kinds.
		*	@param allowMultiple_		Is this property allowed to be attached multiple times to the same entity?
		*	@param shouldInherit_		Should this property be inherited by children when used on structs/classes or virtual methods.
		*/
		PropertySettings(rfk::EEntityKind	targetEntityKind_,
						 bool				allowMultiple_ = false,
						 bool				shouldInherit_ = true)	noexcept;

		rfk_PropertySettings_GENERATED
	};
}

File_PropertySettings_GENERATED