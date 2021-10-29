/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/Misc/EnumMacros.h"

namespace rfk
{
	/**
	*	Describe the kind of an entity
	*/
	enum class EEntityKind : uint16
	{
		/** This entity is... what? Should never happen... */
		Undefined				= 0u,

		/** The entity is a namespace, it can safely be cast to rfk::Namespace type. */
		Namespace				= 1 << 0,

		/** The entity is a class, it can safely be cast to rfk::Class. */
		Class					= 1 << 1,

		/** The archetype is a struct, it can safely be cast to rfk::Struct. */
		Struct					= 1 << 2,

		/** The archetype is an enum, it can safely by cast to rfk::Enum. */
		Enum					= 1 << 3,

		/** The archetype is a fundamental archetype. it can safely by cast to rfk::FundamentalArchetype. */
		FundamentalArchetype	= 1 << 4,

		/** This entity is a (non-member) variable, it can safely be cast to rfk::Variable. */
		Variable				= 1 << 5,

		/**
		*	The entity is a field, it can safely be cast to rfk::FieldBase type.
		*	More specific info can be retrieved from the entity by checking rfk::FieldBase::getFlags().
		*/
		Field					= 1 << 6,

		/** This entity is a (non-member) function, is can safely be cast to rfk::Function. */
		Function				= 1 << 7,

		/**
		*	The entity is a method, it can safely be cast to rfk::MethodBase type.
		*	More specific info can be retrieved from the entity by checking rfk::MethodBase::getFlags().
		*/
		Method					= 1 << 8,

		/** The entity is an enum value, it can safely be cast to rfk::EnumValue. */
		EnumValue				= 1 << 9,

		/** The entity is a namespace fragment, is can safely be cast to rfk::NamespaceFragment. */
		NamespaceFragment		= 1 << 10
	};

	RFK_GENERATE_ENUM_OPERATORS(EEntityKind)
}