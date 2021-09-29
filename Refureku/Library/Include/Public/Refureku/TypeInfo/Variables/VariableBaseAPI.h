/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <utility>		//std::forward, std::move
#include <type_traits>	//std::is_rvalue_reference_v, std::is_lvalue_reference_v, std::is_const_v...

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/TypeAPI.h"

namespace rfk
{
	class VariableBaseAPI : public EntityAPI
	{
		public:
			/**
			*	@brief Get the type of this variable.
			* 
			*	@return The type of the variable.
			*/
			REFUREKU_API TypeAPI const& getType() const noexcept;

		protected:
			//Forward declaration
			class VariableBaseImpl;

			REFUREKU_INTERNAL VariableBaseAPI(VariableBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~VariableBaseAPI()								noexcept;

			/**
			*	@brief Get the data stored in the provided ptr.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam ValueType Type of the data stored in the field.
			*			If ValueType is an rvalue reference, the data is moved into the return value (so the variable is no longer safe to get).
			*			If ValueType is an lvalue reference, return a reference to the variable.
			*			If ValueType is a value type, the data is copied. If it is a struct/class, ValueType must be copy-constructible.
			*
			*	@exception ConstViolation if:
			*		- the variable is const and ValueType is an RValue type (can't move a const field content);
			*		- the variable is const and ValueType is a non-const reference;
			* 
			*	@return The data stored in the ptr.
			*/
			template <typename ValueType>
			[[nodiscard]] ValueType			get(void* ptr)				const;

			/**
			*	@brief Set the provided pointer content.
			*		   This method is not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type of the data to store in the variable.
			*			If ValueType is an rvalue reference, the data is forwarded into the variable.
			*			If ValueType is an lvalue reference, the data is copied into the variable.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename ValueType>
			void							set(void*		ptr,
												ValueType&&	data)		const;

			/**
			*	@brief Copy dataSize bytes starting from data into the variable.
			*
			*	@param data		Address of the data to copy.
			*	@param dataSize Number of bytes to copy into the variable starting from data.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			REFUREKU_INTERNAL void			set(void*		target,
												void const*	source,
												std::size_t	dataSize)	const;

		private:
			/**
			*	@brief Throw a ConstViolation exception with the specified message.
			* 
			*	@param message The message to forward to the exception.
			*/
			REFUREKU_API static void		throwConstViolationException(char const* message);
	};

	#include "Refureku/TypeInfo/Variables/VariableBaseAPI.inl"
}