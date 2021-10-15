/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/FieldBase.h"

namespace rfk
{
	class Field final : public FieldBase
	{
		public:
			REFUREKU_INTERNAL Field(char const*		name,
									std::size_t		id,
									Type const&		type,
									EFieldFlags		flags,
									Struct const*	owner,
									std::size_t		memoryOffset,
									Entity const*	outerEntity = nullptr)	noexcept;
			REFUREKU_INTERNAL Field(Field&&)								noexcept;
			REFUREKU_INTERNAL ~Field()										noexcept;

			/**
			*	@brief Get the value corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type to retrieve from the field.
			*		If ValueType is an rvalue reference, the value is moved into the return value (so the class value is no longer safe to use).
			*		If ValueType is an lvalue reference, return a reference to the field.
			*		If ValueType is a value type, the value is copied. If it is a class, ValueType must be copy-constructible.
			*
			*	@param instance Instance we retrieve the value from.
			* 
			*	@exception ConstViolation if:
			*		- the field is const and ValueType is an RValue type (can't move a const field content);
			*		- the field is const and ValueType is a non-const reference;
			*
			*	@return The queried value in the instance.
			*/
			template <typename ValueType>
			RFK_NODISCARD ValueType					get(void* instance)					const;

			/**
			*	@brief Get the value corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong ValueType.

			*	@note This is only an overload of the same method with a const instance.
			*
			*	@tparam ValueType Type to retrieve from the field.
			*		If ValueType is an rvalue reference, the value is moved into the return value (so the class value is no longer safe to use).
			*		If ValueType is an lvalue reference, return a reference to the field.
			*		If ValueType is a value type, the value is copied. If it is a class, ValueType must be copy-constructible.
			*
			*	@param instance Instance we retrieve the value from.
			*
			*	@return The queried value in the instance.
			*/
			template <typename ValueType>
			RFK_NODISCARD ValueType const			get(void const* instance)			const	noexcept;


			/**
			*	@brief Set the value corresponding to this field in the provided instance.
			*		   This method is not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type to write into the field.
			*		If ValueType is an rvalue reference, the value is forwarded into the instance.
			*		If ValueType is an lvalue reference, the value is copied into the instance.
			*
			*	@param instance Instance we set the value in.
			*	@param value Data to set in the instance.
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*/
			template <typename ValueType>
			void									set(void*		instance,
														ValueType&&	value)				const;

			/**
			*	@brief Copy dataSize bytes starting from valuePtr into this field's address in instance.
			*
			*	@param instance		Instance we write the bytes in.
			*	@param valuePtr		Pointer to the value to copy.
			*	@param valueSize	Number of bytes to copy into the field.
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*/
			REFUREKU_API void						set(void*		instance,
														void const* valuePtr,
														std::size_t	valueSize)			const;

			/**
			*	@brief	Get a pointer to this field in the provided instance.
			*			Performing non-const operations on the pointer if the field is const is undefined behaviour.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Pointer to this field in the provided instance.
			* 
			*	@exception ConstViolation if the field is actually const.
			*/
			RFK_NODISCARD REFUREKU_API void*		getPtr(void* instance)				const;

			/**
			*	@brief Get a const pointer to this field in the provided instance.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Const pointer to this field in the provided instance.
			*/
			RFK_NODISCARD REFUREKU_API void const*	getConstPtr(void const* instance)	const	noexcept;

		protected:
			//Forward declaration
			class FieldImpl;

			GEN_GET_PIMPL(FieldImpl, Entity::getPimpl())
	};

	#include "Refureku/TypeInfo/Variables/Field.inl"
}