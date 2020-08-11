/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <type_traits>
#include <cstring>	//std::memcpy
#include <utility>	//std::forward

#include "Refureku/TypeInfo/Fields/FieldBase.h"
#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class Field : public FieldBase
	{
		public:
			/** Memory offset in bytes of this field in its owner class */
			uint64	memoryOffset	= 0u;

			Field()																= delete;
			Field(std::string&&		name,
				  uint64			id				= 0u,
				  EFieldFlags		flags			= EFieldFlags::Default,
				  Struct const*		ownerStruct		= nullptr,
				  uint64			memoryOffset	= 0u)						noexcept;
			Field(Field const&)													= default;
			Field(Field&&)														= default;
			~Field()															= default;

			/**
			*	@brief Get the data corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	\tparam DataType Type to retrieve from the field.
			*		If DataType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*		If DataType is an lvalue reference, return a reference to the field.
			*		If DataType is a value type, the data is copied. If it is a class, DataType must be copy-constructible.
			*
			*	@param instance Instance we retrieve the data from.
			*
			*	@return The queried data in the instance.
			*/
			template <typename DataType>
			DataType			getData(void* instance)										const noexcept;

			/**
			*	@brief Get the data corresponding to this field in the provided instance.
			*		   This method in not safe if you provide a wrong DataType.

			*	\note This is only an overload of the same method with a const instance.
			*
			*	\tparam DataType Type to retrieve from the field.
			*		If DataType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*		If DataType is an lvalue reference, return a reference to the field.
			*		If DataType is a value type, the data is copied. If it is a class, DataType must be copy-constructible.
			*
			*	@param instance Instance we retrieve the data from.
			*
			*	@return The queried data in the instance.
			*/
			template <typename DataType>
			DataType			getData(void const* instance)								const noexcept;

			
			/**
			*	@brief Set the data corresponding to this field in the provided instance.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	\tparam DataType Type to write into the field.
			*		If DataType is an rvalue reference, the data is forwarded into the instance.
			*		If DataType is an lvalue reference, the data is copied into the instance.
			*
			*	@param instance Instance we set the data in.
			*	@param data Data to set in the instance.
			*/
			template <typename DataType>
			void				setData(void* instance, DataType&& data)					const noexcept;

			/**
			*	@brief Copy dataSize bytes starting from data into this field's address in instance.
			*
			*	@param instance Instance we write the bytes in.
			*	@param data Start address of the written bytes.
			*	@param dataSize Number of bytes to copy
			*/
			inline void			setData(void* instance, void const* data, uint64 dataSize)	const noexcept;

			/**
			*	@brief Get the data address corresponding to this field in the provided instance.
			*
			*	@param instance Instance we get the data address from.
			*
			*	@return Address of the data in instance.
			*/
			inline void*		getDataAddress(void* instance)								const noexcept;

			/**
			*	@brief Get the data address corresponding to this field in the provided instance.
			*
			*	\note This is only an overload of the same method with a const instance.
			*
			*	@param instance Instance we get the data address from.
			*
			*	@return Address of the data in instance.
			*/
			inline void const*	getDataAddress(void const* instance)						const noexcept;
	};

	#include "Refureku/TypeInfo/Fields/Field.inl"
}