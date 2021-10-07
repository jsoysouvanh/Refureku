/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"
#include "Refureku/TypeInfo/Variables/EVarFlags.h"

namespace rfk
{
	class VariableAPI final : public VariableBaseAPI
	{
		public:
			REFUREKU_API		VariableAPI(char const*	name,
											std::size_t	id,
											Type const&	type,
											void*			ptr,
											EVarFlags		flags)		noexcept;
			REFUREKU_API		VariableAPI(char const*	name,
											std::size_t	id,
											Type const&	type,
											void const*	constPtr,
											EVarFlags		flags)		noexcept;
			REFUREKU_INTERNAL	VariableAPI(VariableAPI&&)				noexcept;
			REFUREKU_API		~VariableAPI()							noexcept;

			/**
			*	@brief Get the value stored in this variable.
			*		   This method in not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type of the value stored in the field.
			*			If ValueType is an rvalue reference, the value is moved into the return value (so the variable is no longer safe to get).
			*			If ValueType is an lvalue reference, return a reference to the variable.
			*			If ValueType is a value type, the value is copied. If it is a struct/class, ValueType must be copy-constructible.
			*
			*	@exception ConstViolation if:
			*		- the field is const and ValueType is an RValue type (can't move a const field content);
			*		- the field is const and ValueType is a non-const reference;
			* 
			*	@return The value stored in the variable.
			*/
			template <typename ValueType>
			RFK_NODISCARD ValueType					get()							const;

			/**
			*	@brief Set some value in this variable.
			*		   This method is not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type of the value to store in the variable.
			*			If ValueType is an rvalue reference, the value is forwarded into the variable.
			*			If ValueType is an lvalue reference, the value is copied into the variable.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename ValueType>
			void									set(ValueType&& value)			const;

			/**
			*	@brief Copy dataSize bytes starting from value into the variable.
			*
			*	@param valuePtr		Pointer to the value to copy.
			*	@param valueSize	Number of bytes to copy into the variable.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			REFUREKU_API void						set(void const* valuePtr,
														std::size_t valueSize)		const;

			/**
			*	@brief Check if this variable is static.
			*
			*	@return true if the variable is static, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool			isStatic()						const	noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			RFK_NODISCARD REFUREKU_API EVarFlags	getFlags()						const	noexcept;

			/**
			*	@brief	Get a non-const pointer to this variable.
			*			Performing non-const operations with the pointer if the variable is const is undefined behaviour.
			* 
			*	@return A pointer to this static field.
			*/
			RFK_NODISCARD REFUREKU_API void*		getPtr()						const	noexcept;

			/**
			*	@brief	Get a const pointer to this static field.
			* 
			*	@return A const pointer to this static field.
			*/
			RFK_NODISCARD REFUREKU_API void const*	getConstPtr()					const	noexcept;

		protected:
			//Forward declaration
			class VariableImpl;
	};

	#include "Refureku/TypeInfo/Variables/VariableAPI.inl"
}