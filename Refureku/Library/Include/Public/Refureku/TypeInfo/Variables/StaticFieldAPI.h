/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <type_traits>	//std::is_rvalue_reference_v, std::is_lvalue_reference_v, std::is_const_v...
#include <utility>		//std::forward, std::move

#include "Refureku/TypeInfo/Variables/FieldBaseAPI.h"

namespace rfk
{
	class StaticFieldAPI final : public FieldBaseAPI
	{
		public:
			StaticFieldAPI(char const*		name,
						   std::size_t		id,
						   TypeAPI const&	type,
						   EFieldFlags		flags,
						   StructAPI const*	owner,
						   void*			ptr,
						   EntityAPI const*	outerEntity = nullptr)	noexcept;
			StaticFieldAPI(char const*		name,
						   std::size_t		id,
						   TypeAPI const&	type,
						   EFieldFlags		flags,
						   StructAPI const*	owner,
						   void const*		constPtr,
						   EntityAPI const*	outerEntity = nullptr)	noexcept;
			StaticFieldAPI(StaticFieldAPI&&)						= delete;
			~StaticFieldAPI()										noexcept;
		
			/**
			*	@brief Get the data corresponding to this static field.
			*		   This method in not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type to retrieve from the field.
			*			If ValueType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*			If ValueType is an lvalue reference, return a reference to the field.
			*			If ValueType is a value type, the data is copied. If it is a class, ValueType must be copy-constructible.
			*
			*	@exception ConstViolation if:
			*		- the static field is const and ValueType is an RValue type (can't move a const field content);
			*		- the static field is const and ValueType is a non-const reference;
			* 
			*	@return The queried data.
			*/
			template <typename ValueType>
			[[nodiscard]] ValueType					get()						const;

			/**
			*	@brief Set the data corresponding to this static field.
			*		   This method is not safe if you provide a wrong ValueType.
			*
			*	@tparam ValueType Type to retrieve from the field.
			*			If ValueType is an rvalue reference, the data is forwarded into the static field.
			*			If ValueType is an lvalue reference, the data is copied into the static field.
			* 
			*	@param	value Value to set in the static field.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename ValueType>
			void									set(ValueType&& value)		const;

			/**
			*	@brief Copy dataSize bytes starting from data into the static field.
			*		   This method is not safe if you provide a wrong ValueType.
			*
			*	@param valuePtr		Pointer to the value to copy.
			*	@param valueSize	Number of bytes to copy into the static field.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			REFUREKU_API void						set(void const* valuePtr,
														std::size_t valueSize)	const;

			/**
			*	@brief	Get a non-const pointer to this static field.
			*			Performing non-const operations on the pointer if the static field is const is undefined behaviour.
			* 
			*	@return A pointer to this static field.
			*/
			[[nodiscard]] REFUREKU_API	void*		getPtr()					const	noexcept;

			/**
			*	@brief	Get a const pointer to this static field.
			* 
			*	@return A const pointer to this static field.
			*/
			[[nodiscard]] REFUREKU_API	void const*	getConstPtr()				const	noexcept;

		protected:
			//Forward declaration
			class StaticFieldImpl;
	};

	#include "Refureku/TypeInfo/Variables/StaticFieldAPI.inl"
}