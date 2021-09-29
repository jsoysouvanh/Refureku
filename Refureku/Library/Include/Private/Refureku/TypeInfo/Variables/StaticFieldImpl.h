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
			/** Ptr to the static data. */
			union
			{
				void*		_dataPtr		= nullptr;
				void const*	_constDataPtr;
			};

		public:
			inline StaticFieldImpl(char const*		name,
								   std::size_t		id,
								   TypeAPI const&	type,
								   EFieldFlags		flags,
								   StructAPI const*	owner,
								   void*			dataPtr,
								   EntityAPI const*	outerEntity)	noexcept;
			inline StaticFieldImpl(char const*		name,
								   std::size_t		id,
								   TypeAPI const&	type,
								   EFieldFlags		flags,
								   StructAPI const*	owner,
								   void const*		constDataPtr,
								   EntityAPI const*	outerEntity)	noexcept;

			/**
			*	@brief Getter for the field _dataPtr.
			* 
			*	@return _dataPtr.
			*/
			[[nodiscard]] inline void*			getDataPtr()		const	noexcept;

			/**
			*	@brief Getter for the field _constDataPtr.
			* 
			*	@return _constDataPtr.
			*/
			[[nodiscard]] inline void const*	getConstDataPtr()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Variables/StaticFieldImpl.inl"
}