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
	class FieldAPI final : public FieldBaseAPI
	{
		public:
			FieldAPI(char const*		name,
					 std::size_t		id,
					 TypeAPI const&		type,
					 EFieldFlags		flags,
					 StructAPI const*	owner,
					 std::size_t		memoryOffset,
					 EntityAPI const*	outerEntity = nullptr)	noexcept;
			FieldAPI(FieldAPI&&)								= delete;
			~FieldAPI()											noexcept;

			/**
			*	@brief Get the data corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type to retrieve from the field.
			*		If DataType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*		If DataType is an lvalue reference, return a reference to the field.
			*		If DataType is a value type, the data is copied. If it is a class, DataType must be copy-constructible.
			*
			*	@param instance Instance we retrieve the data from.
			* 
			*	@exception ConstViolation if:
			*		- the field is const and DataType is an RValue type (can't move a const field content);
			*		- the field is const and DataType is a non-const reference;
			*
			*	@return The queried data in the instance.
			*/
			template <typename DataType>
			[[nodiscard]] DataType					getData(void* instance)					const;

			/**
			*	@brief Get the data corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong DataType.

			*	@note This is only an overload of the same method with a const instance.
			*
			*	@tparam DataType Type to retrieve from the field.
			*		If DataType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*		If DataType is an lvalue reference, return a reference to the field.
			*		If DataType is a value type, the data is copied. If it is a class, DataType must be copy-constructible.
			*
			*	@param instance Instance we retrieve the data from.
			*
			*	@return The queried data in the instance.
			*/
			template <typename DataType>
			[[nodiscard]] DataType const			getData(void const* instance)			const	noexcept;


			/**
			*	@brief Set the data corresponding to this field in the provided instance.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type to write into the field.
			*		If DataType is an rvalue reference, the data is forwarded into the instance.
			*		If DataType is an lvalue reference, the data is copied into the instance.
			*
			*	@param instance Instance we set the data in.
			*	@param data Data to set in the instance.
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*/
			template <typename DataType>
			void									setData(void*		instance,
															DataType&&	data)				const;

			/**
			*	@brief Copy dataSize bytes starting from data into this field's address in instance.
			*
			*	@param instance Instance we write the bytes in.
			*	@param data Start address of the written bytes.
			*	@param dataSize Number of bytes to copy
			* 
			*	@exception ConstViolation if the field is actually const and therefore readonly.
			*/
			REFUREKU_API void						setData(void*		instance,
															void const* data,
															std::size_t	dataSize)			const;

			/**
			*	@brief	Get a pointer to this field data in the provided instance.
			*			Performing non-const operations on the pointer if the field is const is undefined behaviour.
			*
			*	@param instance Instance we get the data from.
			*
			*	@return Pointer to this field data in the provided instance.
			*/
			[[nodiscard]] REFUREKU_API void*		getDataPtr(void* instance)				const	noexcept;

			/**
			*	@brief	Get a const pointer to this field data in the provided instance.
			*			This is only an overload of the same method with a const instance.
			*
			*	@param instance Instance we get the data from.
			*
			*	@return Const pointer to this field data in the provided instance.
			*/
			[[nodiscard]] REFUREKU_API void const*	getConstDataPtr(void const* instance)	const	noexcept;

		protected:
			//Forward declaration
			class FieldImpl;
	};

	#include "Refureku/TypeInfo/Variables/FieldAPI.inl"
}