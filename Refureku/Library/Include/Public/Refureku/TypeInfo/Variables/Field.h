/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/FieldBase.h"
#include "Refureku/TypeInfo/Cast.h"
#include "Refureku/TypeInfo/MethodFieldHelpers.h"
#include "Refureku/Exceptions/InvalidArchetype.h"

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
			*	@exception InvalidArchetype if the field can't be accessed from the provided instance.
			*
			*	@return The queried value in the instance.
			*/
			template <typename ValueType, typename InstanceType, typename = std::enable_if_t<is_value_v<InstanceType> && internal::IsAdjustableInstanceValue<InstanceType>>>
			RFK_NODISCARD ValueType		get(InstanceType& instance)						const;

			/**
			*	@brief Get the value corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong ValueType.
			*		   This method DOES NOT perform any pointer adjustment on the provided instance so it is unsafe if instance
			*		   is not a valid pointer to an object of the field's owner archetype.
			*		   Prefer using Field::get for safety if you know the static type of your instance in the calling context.
			*
			*	@note Since this method doesn't perform any pointer adjustment, it is slightly faster than Field::get.
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
			template <typename ValueType>
			RFK_NODISCARD ValueType		getUnsafe(void* instance)						const;

			/**
			*	@brief Get the value corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong ValueType.
			*		   This method DOES NOT perform any pointer adjustment on the provided instance so it is unsafe if instance
			*		   is not a valid pointer to an object of the field's owner archetype.
			*		   Prefer using Field::get for safety if you know the static type of your instance in the calling context.
			*
			*	@note This is only an overload of the same method with a const instance.
			*		  Since this method doesn't perform any pointer adjustment, it is slightly faster than Field::get.
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
			template <typename ValueType>
			RFK_NODISCARD ValueType		getUnsafe(void const* instance)					const;

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
			*	@exception InvalidArchetype if the field can't be accessed from the provided instance.
			*/
			template <typename ValueType, typename InstanceType, typename = std::enable_if_t<is_value_v<InstanceType> && internal::IsAdjustableInstanceValue<InstanceType>>>
			void						set(InstanceType&	instance,
											ValueType&&		value)						const;

			/**
			*	@brief Copy valueSize bytes starting from valuePtr into this field's address in instance.
			*
			*	@param instance		Instance we write the bytes in.
			*	@param valuePtr		Pointer to the value to copy.
			*	@param valueSize	Number of bytes to copy into the field.
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*	@exception InvalidArchetype if the field can't be accessed from the provided instance.
			*/
			template <typename InstanceType, typename = std::enable_if_t<is_value_v<InstanceType> && internal::IsAdjustableInstanceValue<InstanceType>>>
			void						set(InstanceType&	instance,
											void const*		valuePtr,
											std::size_t		valueSize)					const;

			/**
			*	@brief Set the value corresponding to this field in the provided instance.
			*		   This method is not safe if you provide a wrong ValueType.
			*		   This method DOES NOT perform any pointer adjustment on the provided instance so it is unsafe if instance
			*		   is not a valid pointer to an object of the field's owner archetype.
			*		   Prefer using Field::set for safety if you know the static type of your instance in the calling context.
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
			void						setUnsafe(void*			instance,
												  ValueType&&	value)					const;

			/**
			*	@brief Copy valueSize bytes starting from valuePtr into this field's address in instance.
			*
			*	@param instance		Instance we write the bytes in.
			*	@param valuePtr		Pointer to the value to copy.
			*	@param valueSize	Number of bytes to copy into the field.
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*/
			REFUREKU_API void			setUnsafe(void*			instance,
												  void const*	valuePtr,
												  std::size_t	valueSize)				const;

			/**
			*	@brief	Get a pointer to this field in the provided instance.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Pointer to this field in the provided instance.
			* 
			*	@exception ConstViolation if the field is actually const.
			*	@exception InvalidArchetype if the field can't be accessed from the provided instance.
			*/
			template <typename InstanceType, typename = std::enable_if_t<is_value_v<InstanceType> && internal::IsAdjustableInstanceValue<InstanceType>>>
			RFK_NODISCARD void*			getPtr(InstanceType& instance)					const;

			/**
			*	@brief Get a pointer to this field in the provided instance.
			*		   This method DOES NOT perform any pointer adjustment on the provided instance so it is unsafe if instance
			*		   is not a valid pointer to an object of the field's owner archetype.
			*		   Prefer using Field::getPtr for safety if you know the static type of your instance in the calling context.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Pointer to this field in the provided instance.
			* 
			*	@exception ConstViolation if the field is actually const.
			*	@exception InvalidArchetype if the field can't be accessed from the provided instance.
			*/
			RFK_NODISCARD REFUREKU_API 
				void*					getPtrUnsafe(void* instance)					const;

			/**
			*	@brief Get a const pointer to this field in the provided instance.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Const pointer to this field in the provided instance.
			* 
			*	@exception InvalidArchetype if the field can't be accessed from the provided instance.
			*/
			template <typename InstanceType, typename = std::enable_if_t<is_value_v<InstanceType> && internal::IsAdjustableInstanceValue<InstanceType>>>
			RFK_NODISCARD void const*	getConstPtr(InstanceType const& instance)		const;

			/**
			*	@brief Get a const pointer to this field in the provided instance.
			*		   This method DOES NOT perform any pointer adjustment on the provided instance so it is unsafe if instance
			*		   is not a valid pointer to an object of the field's owner archetype.
			*		   Prefer using Field::getConstPtr for safety if you know the static type of your instance in the calling context.
			*
			*	@param instance Instance we get the field from.
			*
			*	@return Const pointer to this field in the provided instance.
			*/
			RFK_NODISCARD REFUREKU_API
				void const*				getConstPtrUnsafe(void const* instance)			const	noexcept;

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
			/**
			*	@brief Adjust the instance pointer to a pointer to this field's owner struct.
			* 
			*	@tparam InstanceType The static type of the provided instance.
			* 
			*	@param instance The instance to adjust.
			* 
			*	@return The adjusted instance pointer.
			* 
			*	@exception InvalidArchetype if the instance dynamic archetype is different from the field's owner struct.
			*/
			template <typename InstanceType>
			RFK_NODISCARD InstanceType*	adjustInstancePointerAddress(InstanceType* instance) const;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Field const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Field const*, rfk::Allocator<Field const*>>);

	#include "Refureku/TypeInfo/Variables/Field.inl"
}