/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/Object.h"
#include "Refureku/TypeInfo/Entity.h"

#include "Refureku/Generated/Property.rfk.h"

namespace rfk RFKNamespace()
{
	struct RFKStruct() Property : public Object
	{
		public:
			/** Kind of entity this property can be attached to. */
			static constexpr rfk::Entity::EKind targetEntityKind	= rfk::Entity::EKind::Class | rfk::Entity::EKind::Struct;

			/** Should this property be inherited? */
			static constexpr bool				shouldInherit		= true;
			
			/** Is this property allowed to be attached multiple times to the same entity? */
			static constexpr bool				allowMultiple		= false;

			Property()					= default;
			Property(Property const&)	= delete;
			Property(Property&&)		= delete;
			virtual ~Property()			= default;

		Property_GENERATED
	};
}

File_GENERATED