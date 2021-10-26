/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/FieldBase.h"
#include "Refureku/TypeInfo/Variables/VariableBaseImpl.h"

namespace rfk
{
	class FieldBase::FieldBaseImpl : public VariableBase::VariableBaseImpl
	{
		private:
			/** Flags describing this field. */
			EFieldFlags			_flags	= EFieldFlags::Default;

			/** Struct owning this field. */
			Struct const*	_owner	= nullptr;

		public:
			inline FieldBaseImpl(char const*		name,
								 std::size_t		id,
								 Type const&		type,
								 EFieldFlags		flags,
								 Struct const*	owner,
								 Entity const*	outerEntity = nullptr)	noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			inline EFieldFlags		getFlags()	const	noexcept;

			/**
			*	@brief Getter for the field _owner.
			* 
			*	@return _owner.
			*/
			inline Struct const*	getOwner()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Variables/FieldBaseImpl.inl"
}