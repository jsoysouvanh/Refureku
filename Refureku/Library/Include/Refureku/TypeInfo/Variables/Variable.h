/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>
#include <cstring>		//std::memcpy
#include <utility>		//std::forward
#include <cassert>

#include "Refureku/TypeInfo/Variables/VariableBase.h"
#include "Refureku/TypeInfo/Variables/EVarFlags.h"
#include "Refureku/Misc/FundamentalTypes.h"

namespace rfk
{
	class Variable final : public VariableBase
	{
		public:
			/** Address of this variable in memory. */
			void*		address	= nullptr;

			/** Flags describing this variable. */
			EVarFlags	flags	= EVarFlags::Default;

			Variable()							= delete;
			Variable(std::string&&	name,
					 uint64			id,
					 Type const&	type,
					 void*			address,
					 EVarFlags		flags)		noexcept;
			Variable(Variable const&)			= delete;
			Variable(Variable&&)				= delete;
			~Variable()							= default;

			/**
			*	@brief Get the data stored in this variable.
			*		   This method in not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type of the data stored in the field.
			*			If DataType is an rvalue reference, the data is moved into the return value (so the variable is no longer safe to get).
			*			If DataType is an lvalue reference, return a reference to the variable.
			*			If DataType is a value type, the data is copied. If it is a struct/class, DataType must be copy-constructible.
			*
			*	@return The data stored in the variable.
			*/
			template <typename DataType>
			DataType		getData()									const noexcept;

			/**
			*	@brief Set some data in this variable.
			*		   This method is not safe if you provide a wrong DataType.
			*
			*	@tparam DataType Type of the data to store in the variable.
			*			If DataType is an rvalue reference, the data is forwarded into the variable.
			*			If DataType is an lvalue reference, the data is copied into the variable.
			*/
			template <typename DataType>
			void			setData(DataType&& data)					const noexcept;

			/**
			*	@brief Copy dataSize bytes starting from data into the variable.
			*
			*	@param data Address of the data to copy.
			*	@param dataSize Number of bytes to copy into the variable starting from data.
			*/
			inline void		setData(void const* data, uint64 dataSize)	const noexcept;

			/**
			*	@brief Check if this variable is static.
			*
			*	@return true if the variable is static, else false.
			*/
			bool			isStatic()									const noexcept;
	};

	#include "Refureku/TypeInfo/Variables/Variable.inl"
}