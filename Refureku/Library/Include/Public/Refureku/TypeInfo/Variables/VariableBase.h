/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cassert>
#include <utility>		//std::forward, std::move
#include <type_traits>	//std::is_rvalue_reference_v, std::is_lvalue_reference_v, std::is_const_v...

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class VariableBase : public Entity
	{
		public:
			/**
			*	@brief Get the type of this variable.
			* 
			*	@return The type of the variable.
			*/
			REFUREKU_API Type const& getType() const noexcept;

		protected:
			//Forward declaration
			class VariableBaseImpl;

			template <typename T>
			static constexpr bool is_value_v = !std::is_lvalue_reference_v<T> && !std::is_rvalue_reference_v<T>;

			REFUREKU_INTERNAL VariableBase(VariableBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL VariableBase(VariableBase&&)						noexcept;
			REFUREKU_INTERNAL ~VariableBase()									noexcept;

			RFK_GEN_GET_PIMPL(VariableBaseImpl, Entity::getPimpl())

			/**
			*	@brief Get the data stored in the provided ptr.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam ValueType Type of the data stored in the field.
			*			If ValueType is an rvalue reference, the data is moved into the return value (so the variable is no longer safe to get).
			*			If ValueType is an lvalue reference, return a reference to the variable.
			*			If ValueType is a value type, the data is copied. If it is a struct/class, ValueType must be copy-constructible.
			*
			*	@param ptr Pointer to the variable to get.
			* 
			*	@return The data stored in the ptr.
			* 
			*	@exception ConstViolation if:
			*		- the variable is const and ValueType is an RValue type (can't move a const field content);
			*		- the variable is const and ValueType is a non-const reference;
			*/
			template <typename ValueType>
			RFK_NODISCARD ValueType					get(void* ptr)				const;

			/**
			*	@brief	Get the data stored in the provided ptr.
			*			This method in not safe if you provide a wrong DataType.
			*			Overload of the same method for const pointers.
			*
			*	@tparam ValueType Type of the data stored in the field.
			*			If ValueType is an rvalue reference, the data is moved into the return value (so the variable is no longer safe to get).
			*			If ValueType is an lvalue reference, return a reference to the variable.
			*			If ValueType is a value type, the data is copied. If it is a struct/class, ValueType must be copy-constructible.
			*
			*	@param ptr Pointer to the variable to get.
			* 
			*	@return The data stored in the ptr.
			* 
			*	@exception ConstViolation if:
			*		- the variable is const and ValueType is an RValue type (can't move a const field content);
			*		- the variable is const and ValueType is a non-const reference;
			*/
			template <typename ValueType>
			RFK_NODISCARD ValueType					get(void const* ptr)		const;

			/**
			*	@brief Set the provided pointer content.
			*		   This method is not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type of the data to store in the variable.
			*			If ValueType is an rvalue reference, the data is forwarded into the variable.
			*			If ValueType is an lvalue reference, the data is copied into the variable.
			* 
			*	@param ptr		Pointer to the variable to set.
			*	@param value	New value.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename ValueType>
			void									set(void*		ptr,
														ValueType&&	value)		const;

			/**
			*	@brief Copy dataSize bytes starting from data into the variable.
			*
			*	@param target		Pointer to the memory to set.
			*	@param source		Pointer to the memory to from from.
			*	@param bytesCount	Number of bytes to copy.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			REFUREKU_INTERNAL void					set(void*		target,
														void const*	source,
														std::size_t	bytesCount)	const;

			/**
			*	@brief	Throw a ConstViolation exception with the specified message.
			*			/!\ This method is called from template methods so it must be exported.
			* 
			*	@param message The message to forward to the exception.
			*/
			RFK_NORETURN REFUREKU_API static void	throwConstViolationException(char const* message);
	};

	#include "Refureku/TypeInfo/Variables/VariableBase.inl"
}