/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/ETypePartDescriptor.h"

namespace rfk
{
	class TypePartAPI
	{
		public:
			using AdditionalDataType = uint32;

		private:
			/** Some additional data which might complement descriptor (for example CArray size) */
			AdditionalDataType	_additionalData	= 0u;

			/** Actual data describing this type part */
			ETypePartDescriptor	_descriptor		= ETypePartDescriptor::Undefined;

		public:
			TypePartAPI()									= default;
			TypePartAPI(ETypePartDescriptor	descriptor,
						AdditionalDataType	additionalData)	noexcept;
			TypePartAPI(TypePartAPI const&)					= default;
			TypePartAPI(TypePartAPI&&)						= default;

			/**
			*	@brief	Add a flag to the descriptor field.
			* 
			*	@param flag The flag to add this this type part descriptor.
			*/
			REFUREKU_API void				addDescriptorFlag(ETypePartDescriptor flag)	noexcept;

			REFUREKU_API bool				isPointer()							const	noexcept;
			REFUREKU_API bool				isLValueReference()					const	noexcept;
			REFUREKU_API bool				isRValueReference()					const	noexcept;
			REFUREKU_API bool				isCArray()							const	noexcept;
			REFUREKU_API bool				isValue()							const	noexcept;
			REFUREKU_API bool				isConst()							const	noexcept;
			REFUREKU_API bool				isVolatile()						const	noexcept;
			REFUREKU_API AdditionalDataType	getCArraySize()						const	noexcept;

			/**
			*	@brief Setter for the field _additionalData.
			* 
			*	@param data The data to set.
			*/
			REFUREKU_API void				setAdditionalData(AdditionalDataType data)	noexcept;

			TypePartAPI&	operator=(TypePartAPI const&)	= default;
			TypePartAPI&	operator=(TypePartAPI&&)		= default;
	};
}