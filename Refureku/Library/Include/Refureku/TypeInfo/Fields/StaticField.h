/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <type_traits>
#include <cstring>		//std::memcpy
#include <utility>		//std::forward

#include "Refureku/TypeInfo/Fields/FieldBase.h"
#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class StaticField : public FieldBase
	{
		private:
			/** Address of the field data. */
			void*	dataAddress	= nullptr;

		public:
			StaticField()																	= delete;
			StaticField(std::string&&		name,
						uint64				id				= 0u,
						EFieldFlags			flags			= EFieldFlags::Static,
						Struct const*		ownerStruct		= nullptr,
						void*				ptrToData		= nullptr)						noexcept;
			StaticField(StaticField const&)													= default;
			StaticField(StaticField&&)														= default;
			~StaticField()																	= default;

			/**
			*	@brief Get the data corresponding to this static field.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type to retrieve from the field.
			*			If DataType is an rvalue reference, the data is moved into the return value (so the class data is no longer safe to use).
			*			If DataType is an lvalue reference, return a reference to the field.
			*			If DataType is a value type, the data is copied. If it is a class, DataType must be copy-constructible.
			*
			*	@return The queried data.
			*/
			template <typename DataType>
			DataType		getData()									const noexcept;

			/**
			*	@brief Set the data corresponding to this static field.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type to retrieve from the field.
			*			If DataType is an rvalue reference, the data is forwarded into the static field.
			*			If DataType is an lvalue reference, the data is copied into the static field.
			*/
			template <typename DataType>
			void			setData(DataType&& data)					const noexcept;

			/**
			*	@brief Copy dataSize bytes starting from data into the static field.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@param data Address of the data to copy.
			*	@param dataSize Number of bytes to copy into the static field starting from data.
			*/
			inline void		setData(void const* data, uint64 dataSize)	const noexcept;

			/**
			*	@return The data address corresponding to this static field.
			*/
			inline void*	getDataAddress()							const noexcept;
	};

	#include "Refureku/TypeInfo/Fields/StaticField.inl"
}