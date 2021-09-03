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

#include "Refureku/TypeInfo/Variables/FieldBase.h"
#include "Refureku/TypeInfo/Type.h"
#include "Refureku/Exceptions/ConstViolation.h"

namespace rfk
{
	class StaticField final : public FieldBase
	{
		private:
			/** Address of the field data. */
			union
			{
				void*		_address		= nullptr;
				void const*	_constAddress;
			};

			/**
			*	@return The data address corresponding to this static field.
			*/
			inline void*	getAddress()	const noexcept;

		public:
			StaticField()								= delete;
			StaticField(std::string&&	name,
						uint64			id,
						Type const&		type,
						EFieldFlags		flags,
						Struct const*	ownerStruct,
						void*			address)		noexcept;
			StaticField(std::string&&	name,
						uint64			id,
						Type const&		type,
						EFieldFlags		flags,
						Struct const*	ownerStruct,
						void const*		address)		noexcept;
			StaticField(StaticField const&)				= delete;
			StaticField(StaticField&&)					= delete;

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
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			template <typename DataType>
			void			setData(DataType&& data)					const;

			/**
			*	@brief Copy dataSize bytes starting from data into the static field.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@param data Address of the data to copy.
			*	@param dataSize Number of bytes to copy into the static field starting from data.
			* 
			*	@exception ConstViolation if the variable is actually const and therefore readonly.
			*/
			inline void		setData(void const* data, uint64 dataSize)	const;

			StaticField& operator=(StaticField const&)	= delete;
			StaticField& operator=(StaticField&&)		= delete;
	};

	#include "Refureku/TypeInfo/Variables/StaticField.inl"
}