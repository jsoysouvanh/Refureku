/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBase.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"
#include "Refureku/TypeInfo/Variables/EFieldFlags.h"

namespace rfk
{
	class Struct;	//Forward declaration

	class FieldBase : public VariableBase
	{
		private:
			/** Flags describing this field. */
			EFieldFlags		_flags			= EFieldFlags::Default;

			/** Struct containing this field. */
			Struct const*	_containedIn	= nullptr;

		protected:
			FieldBase(std::string&&	name,
					  uint64		id,
					  Type const&	type,
					  EFieldFlags	flags,
					  Struct const*	containedIn,
					  Entity const*	outerEntity = nullptr)	noexcept;
			FieldBase(FieldBase const&)						= delete;
			FieldBase(FieldBase&&)							= delete;

		public:
			/**
			*	@return The access specifier of this field in its owner struct/class.
			*/
			REFUREKU_API EAccessSpecifier	getAccess()			const	noexcept;

			/**
			*	@return true if this field is static, else false.
			*/
			inline bool						isStatic()			const	noexcept;

			/**
			*	@return true if this field is mutable, else false
			*/
			inline bool						isMutable()			const	noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			inline EFieldFlags				getFlags()			const	noexcept;

			/**
			*	@brief Getter for the field _containedIn.
			* 
			*	@return _containedIn.
			*/
			inline Struct const*			getContainedIn()	const	noexcept;


			FieldBase& operator=(FieldBase const&)	= delete;
			FieldBase& operator=(FieldBase&&)		= delete;
	};

	#include "Refureku/TypeInfo/Variables/FieldBase.inl"
}