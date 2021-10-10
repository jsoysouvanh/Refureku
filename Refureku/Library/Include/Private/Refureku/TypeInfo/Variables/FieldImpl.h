/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/FieldBaseImpl.h"

namespace rfk
{
	class Field::FieldImpl final : public FieldBase::FieldBaseImpl
	{
		private:
			/** Memory offset in bytes of this field in its owner class. */
			std::size_t	_memoryOffset	= 0u;

		public:
			inline FieldImpl(char const*		name,
							 std::size_t		id,
							 Type const&		type,
							 EFieldFlags		flags,
							 Struct const*	owner,
							 std::size_t		memoryOffset,
							 Entity const*	outerEntity = nullptr)	noexcept;

			/**
			*	@brief Getter for the field _memoryOffset.
			* 
			*	@return _memoryOffset.
			*/
			inline std::size_t	getMemoryOffset()						const	noexcept;
	};

	#include "Refureku/TypeInfo/Variables/FieldImpl.inl"
}