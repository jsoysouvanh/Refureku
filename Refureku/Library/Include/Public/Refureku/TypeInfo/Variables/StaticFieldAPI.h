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
#include "Refureku/Exceptions/ConstViolation.h"

namespace rfk
{
	class StaticFieldAPI : public FieldBaseAPI
	{
		public:
			StaticFieldAPI(char const*		name,
						   std::size_t		id,
						   TypeAPI const&	type,
						   EFieldFlags		flags,
						   StructAPI const*	owner,
						   void*			dataPtr,
						   EntityAPI const*	outerEntity = nullptr)	noexcept;
			StaticFieldAPI(char const*		name,
						   std::size_t		id,
						   TypeAPI const&	type,
						   EFieldFlags		flags,
						   StructAPI const*	owner,
						   void const*		constDataPtr,
						   EntityAPI const*	outerEntity = nullptr)	noexcept;
			StaticFieldAPI(StaticFieldAPI&&)						= delete;
			~StaticFieldAPI()										noexcept;
		
			/**
			*	@brief Get the data corresponding to this static field.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type to retrieve from the field.
			*			If DataType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*			If DataType is an lvalue reference, return a reference to the field.
			*			If DataType is a value type, the data is copied. If it is a class, DataType must be copy-constructible.
			*
			*	@exception ConstViolation if:
			*		- the field is const and DataType is an RValue type (can't move a const field content);
			*		- the field is const and DataType is a non-const reference;
			* 
			*	@return The queried data.
			*/
			template <typename DataType>
			[[nodiscard]] DataType					getData()										const;

			/**
			*	@brief Set the data corresponding to this static field.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type to retrieve from the field.
			*			If DataType is an rvalue reference, the data is forwarded into the static field.
			*			If DataType is an lvalue reference, the data is copied into the static field.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename DataType>
			void									setData(DataType&& data)						const;

			/**
			*	@brief Copy dataSize bytes starting from data into the static field.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@param data Address of the data to copy.
			*	@param dataSize Number of bytes to copy into the static field starting from data.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			REFUREKU_API void						setData(void const* data, std::size_t dataSize)	const;

			/**
			*	@brief	Get a non-const pointer to this static field data.
			*			Performing non-const operations if the static field is const is undefined behaviour.
			* 
			*	@return A pointer to this static field data.
			*/
			[[nodiscard]] REFUREKU_API	void*		getDataPtr()									const	noexcept;

			/**
			*	@brief	Get a const pointer to this static field data.
			* 
			*	@return A const pointer to this static field data.
			*/
			[[nodiscard]] REFUREKU_API	void const*	getConstDataPtr()								const	noexcept;

		protected:
			//Forward declaration
			class StaticFieldImpl;
	};

	#include "Refureku/TypeInfo/Variables/StaticFieldAPI.inl"
}