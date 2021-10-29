/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Object.h"
#include "Refureku/Containers/Vector.h"
#include "Refureku/TypeInfo/Entity/EEntityKind.h"
#include "Refureku/Misc/Visitor.h"
#include "Refureku/Misc/Predicate.h"

namespace rfk
{
	/**
	*	@brief Base class to inherit from to define new properties.
	*/
	class REFUREKU_API Property : public Object
	{
		protected:
			Property() = default;

		public:
			/** Kind of entity this property can be attached to. By default, a property can be attached to any kind of entity. */
			static constexpr rfk::EEntityKind	targetEntityKind	=	rfk::EEntityKind::Class | rfk::EEntityKind::Enum | rfk::EEntityKind::EnumValue |
																		rfk::EEntityKind::Field |rfk::EEntityKind::Function | rfk::EEntityKind::Method |
																		rfk::EEntityKind::Namespace | rfk::EEntityKind::Struct | rfk::EEntityKind::Variable;

			/** Should this property be inherited in child struct/class? Relevant only for properties targeting structs/classes. */
			static constexpr bool				shouldInherit		= true;
			
			/** Is this property allowed to be attached multiple times to the same entity? */
			static constexpr bool				allowMultiple		= false;

			/**
			*	@brief Getter for targetEntityKind of the concrete Property type.
			*	
			*	@return targetEntityKind.
			*/
			virtual rfk::EEntityKind	getTargetEntityKind()	const noexcept;

			/**
			*	@brief Getter for shouldInherit of the concrete Property type.
			*	
			*	@return shouldInherit.
			*/
			virtual bool				getShouldInherit()		const noexcept;

			/**
			*	@brief Getter for allowMultiple of the concrete Property type.
			*	
			*	@return allowMultiple.
			*/
			virtual bool				getAllowMultiple()		const noexcept;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Property const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Property const*, rfk::Allocator<Property const*>>);
}