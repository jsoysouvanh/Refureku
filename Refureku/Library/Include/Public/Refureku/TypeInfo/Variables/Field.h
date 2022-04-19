/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
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
			*		If ValueType is an rvalue reference, the field value is moved into the return value (so the field value is no longer safe to use).
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
			template <typename ValueType, typename OwnerStructType, typename = std::enable_if_t<is_value_v<OwnerStructType>>>
			RFK_NODISCARD ValueType		get(OwnerStructType& instance)					const;

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
			template <typename ValueType, typename OwnerStructType, typename = std::enable_if_t<is_value_v<OwnerStructType>>>
			RFK_NODISCARD ValueType		get(OwnerStructType const& instance)			const;

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
			template <typename ValueType, typename OwnerStructType, typename = std::enable_if_t<is_value_v<OwnerStructType>>>
			void						set(OwnerStructType&	instance,
											ValueType&&			value)					const;

			/**
			*	@brief Copy valueSize bytes starting from valuePtr into this field's address in instance.
			*
			*	@param instance		Instance we write the bytes in.
			*	@param valuePtr		Pointer to the value to copy.
			*	@param valueSize	Number of bytes to copy into the field.
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*/
			template <typename OwnerStructType, typename = std::enable_if_t<is_value_v<OwnerStructType>>>
			void						set(OwnerStructType&	instance,
											void const*			valuePtr,
											std::size_t			valueSize)				const;

			/**
			*	@brief	Get a pointer to this field in the provided instance.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Pointer to this field in the provided instance.
			* 
			*	@exception ConstViolation if the field is actually const.
			*/
			template <typename OwnerStructType, typename = std::enable_if_t<is_value_v<OwnerStructType>>>
			RFK_NODISCARD void*			getPtr(OwnerStructType& instance)				const;

			/**
			*	@brief Get a const pointer to this field in the provided instance.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Const pointer to this field in the provided instance.
			*/
			template <typename OwnerStructType, typename = std::enable_if_t<is_value_v<OwnerStructType>>>
			RFK_NODISCARD void const*	getConstPtr(OwnerStructType const& instance)	const	noexcept;

			/**
			*	@brief Get the memory offset of this field in an instance of its owner class (Field::getOwner()).
			* 
			*	@return The memory offset in bytes.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t
										getMemoryOffset()								const	noexcept;

		protected:
			//Forward declaration
			class FieldImpl;

			RFK_GEN_GET_PIMPL(FieldImpl, Entity::getPimpl())

		private:
			template <typename ValueType>
			RFK_NODISCARD ValueType					getInternal(void* instance)					const;

			template <typename ValueType>
			RFK_NODISCARD ValueType const			getInternal(void const* instance)			const	noexcept;

			template <typename ValueType>
			void									setInternal(void*		instance,
																ValueType&&	value)				const;

			REFUREKU_API void						setInternal(void*		instance,
																void const* valuePtr,
																std::size_t	valueSize)			const;

			RFK_NODISCARD REFUREKU_API void*		getPtrInternal(void* instance)				const;

			RFK_NODISCARD REFUREKU_API void const*	getConstPtrInternal(void const* instance)	const	noexcept;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Field const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Field const*, rfk::Allocator<Field const*>>);

	#include "Refureku/TypeInfo/Variables/Field.inl"
}