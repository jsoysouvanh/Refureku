/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Variables/FieldBaseImpl.h"

namespace rfk
{
	class StaticField::StaticFieldImpl : public FieldBase::FieldBaseImpl
	{
		private:
			/** Ptr to the static field. */
			union
			{
				void*		_ptr		= nullptr;
				void const*	_constPtr;
			};

		public:
			inline StaticFieldImpl(char const*		name,
								   std::size_t		id,
								   char const*      canonicalTypeName,
								   Type const&	    type,
								   EFieldFlags		flags,
								   Struct const*	owner,
								   void*			ptr,
								   Entity const*	outerEntity)	noexcept;
			inline StaticFieldImpl(char const*		name,
								   std::size_t		id,
								   char const*      canonicalTypeName,
								   Type const&	    type,
								   EFieldFlags		flags,
								   Struct const*	owner,
								   void const*		constPtr,
								   Entity const*	outerEntity)	noexcept;

			/**
			*	@brief Getter for the field _ptr.
			* 
			*	@return _ptr.
			*/
			RFK_NODISCARD inline void*			getPtr()		const	noexcept;

			/**
			*	@brief Getter for the field _constPtr.
			* 
			*	@return _constPtr.
			*/
			RFK_NODISCARD inline void const*	getConstPtr()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Variables/StaticFieldImpl.inl"
}