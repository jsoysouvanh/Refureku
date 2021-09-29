/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <utility>		//std::forward
#include <type_traits>	//std::is_rvalue_reference_v, std::is_lvalue_reference_v, std::is_const_v...

#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"
#include "Refureku/TypeInfo/Variables/EVarFlags.h"
#include "Refureku/Exceptions/ConstViolation.h"

namespace rfk
{
	class VariableAPI : public VariableBaseAPI
	{
		public:
			REFUREKU_API VariableAPI(char const*	name,
									 std::size_t	id,
									 TypeAPI const&	type,
									 void*			dataPtr,
									 EVarFlags		flags)		noexcept;
			REFUREKU_API VariableAPI(char const*	name,
									 std::size_t	id,
									 TypeAPI const&	type,
									 void const*	constDataPtr,
									 EVarFlags		flags)		noexcept;
			REFUREKU_API ~VariableAPI()							noexcept;

			/**
			*	@brief Get the data stored in this variable.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type of the data stored in the field.
			*			If DataType is an rvalue reference, the data is moved into the return value (so the variable is no longer safe to get).
			*			If DataType is an lvalue reference, return a reference to the variable.
			*			If DataType is a value type, the data is copied. If it is a struct/class, DataType must be copy-constructible.
			*
			*	@exception ConstViolation if:
			*		- the field is const and DataType is an RValue type (can't move a const field content);
			*		- the field is const and DataType is a non-const reference;
			* 
			*	@return The data stored in the variable.
			*/
			template <typename DataType>
			[[nodiscard]] DataType					get()							const;

			/**
			*	@brief Set some data in this variable.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type of the data to store in the variable.
			*			If DataType is an rvalue reference, the data is forwarded into the variable.
			*			If DataType is an lvalue reference, the data is copied into the variable.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename DataType>
			void									set(DataType&& data)			const;

			/**
			*	@brief Copy dataSize bytes starting from data into the variable.
			*
			*	@param data		Address of the data to copy.
			*	@param dataSize Number of bytes to copy into the variable starting from data.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			REFUREKU_API void						set(void const* data,
														std::size_t dataSize)		const;

			/**
			*	@brief Check if this variable is static.
			*
			*	@return true if the variable is static, else false.
			*/
			[[nodiscard]] REFUREKU_API bool			isStatic()						const	noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			[[nodiscard]] REFUREKU_API EVarFlags	getFlags()						const	noexcept;

			/**
			*	@brief	Get a non-const pointer to this variable.
			*			Performing non-const operations with the pointer if the variable is const is undefined behaviour.
			* 
			*	@return A pointer to this static field data.
			*/
			[[nodiscard]] REFUREKU_API	void*		getPtr()						const	noexcept;

			/**
			*	@brief	Get a const pointer to this static field data.
			* 
			*	@return A const pointer to this static field data.
			*/
			[[nodiscard]] REFUREKU_API	void const*	getConstPtr()					const	noexcept;

		protected:
			//Forward declaration
			class VariableImpl;
	};

	#include "Refureku/TypeInfo/Variables/VariableAPI.inl"
}