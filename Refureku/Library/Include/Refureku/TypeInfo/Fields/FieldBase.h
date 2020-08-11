/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"
#include "Refureku/TypeInfo/Type.h"
#include "Refureku/TypeInfo/Fields/EFieldFlags.h"

namespace rfk
{
	class Struct;	//Forward declaration

	class FieldBase : public Entity
	{
		protected:
			FieldBase()															= delete;
			FieldBase(std::string&&		name,
					  uint64			id				= 0u,
					  EFieldFlags		flags			= EFieldFlags::Default,
					  Struct const*		ownerStruct		= nullptr)				noexcept;
			FieldBase(FieldBase const&)											= default;
			FieldBase(FieldBase&&)												= default;
			~FieldBase()														= default;

		public:
			/** Flags describing this field. */
			EFieldFlags			flags	= EFieldFlags::Default;

			/** Type of this field. */
			Type				type;
			
			/** Struct this field belongs to. */
			Struct const*		ownerStruct;

			/**
			*	@return The access specifier of this field in its owner struct/class.
			*/
			EAccessSpecifier	getAccess()		const	noexcept;

			/**
			*	@return true if this field is static, else false.
			*/
			bool				isStatic()		const	noexcept;

			/**
			*	@return true if this field is mutable, else false
			*/
			bool				isMutable()		const	noexcept;
	};
}