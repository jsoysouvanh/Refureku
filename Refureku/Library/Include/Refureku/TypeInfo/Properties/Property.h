/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Object.h"
#include "Refureku/TypeInfo/Entity/EEntityKind.h"

namespace rfk
{
	/**
	*	@brief Base struct to inherit from to define new properties.
	*/
	struct Property : public Object
	{
		protected:
			Property()	= default;

		public:
			/** Kind of entity this property can be attached to. */
			static constexpr rfk::EEntityKind	targetEntityKind	=	rfk::EEntityKind::Class | rfk::EEntityKind::Enum | rfk::EEntityKind::EnumValue |
																		rfk::EEntityKind::Field |rfk::EEntityKind::Function | rfk::EEntityKind::Method |
																		rfk::EEntityKind::Namespace | rfk::EEntityKind::Struct | rfk::EEntityKind::Variable;

			/** Should this property be inherited? */
			static constexpr bool				shouldInherit		= true;
			
			/** Is this property allowed to be attached multiple times to the same entity? */
			static constexpr bool				allowMultiple		= false;

			Property(Property const&)	= delete;
			Property(Property&&)		= delete;
	};
}