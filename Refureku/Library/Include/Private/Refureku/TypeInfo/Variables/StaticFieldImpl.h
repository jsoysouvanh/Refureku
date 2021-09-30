/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"
#include "Refureku/TypeInfo/Variables/FieldBaseImpl.h"

namespace rfk
{
	class StaticFieldAPI::StaticFieldImpl : public FieldBaseAPI::FieldBaseImpl
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
								   TypeAPI const&	type,
								   EFieldFlags		flags,
								   StructAPI const*	owner,
								   void*			ptr,
								   EntityAPI const*	outerEntity)	noexcept;
			inline StaticFieldImpl(char const*		name,
								   std::size_t		id,
								   TypeAPI const&	type,
								   EFieldFlags		flags,
								   StructAPI const*	owner,
								   void const*		constPtr,
								   EntityAPI const*	outerEntity)	noexcept;

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