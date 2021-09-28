/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/Config.h"
#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/Utility/EnumMacros.h"
#include "Refureku/TypeInfo/ETypePartDescriptor.h"

namespace rfk
{
	class REFUREKU_API TypePart
	{
		public:
			/**
			*	Padding to make sure sizeof(TypePart) is exactly 64 bits.
			*	This is necessary since type parts are compared using std::memcmp
			*	so all the memory must be initialized.
			*/
			uint16				padding			= 0u;

			/** Actual data describing this type part */
			ETypePartDescriptor	descriptor		= ETypePartDescriptor::Undefined;
			
			/** Some additional data which might complement descriptor (for example CArray size) */
			uint32				additionalData	= 0u;

			TypePart()																		= default;
			TypePart(uint16 padding, ETypePartDescriptor descriptor, uint32 additionalData)	noexcept;
			TypePart(TypePart const&)														= default;
			TypePart(TypePart&&)															= default;

			inline bool		isPointer()			const	noexcept;
			inline bool		isLValueReference()	const	noexcept;
			inline bool		isRValueReference()	const	noexcept;
			inline bool		isCArray()			const	noexcept;
			inline bool		isValue()			const	noexcept;
			inline bool		isConst()			const	noexcept;
			inline bool		isVolatile()		const	noexcept;
			inline uint32	getArraySize()		const	noexcept;

			TypePart&	operator=(TypePart const&)	= default;
			TypePart&	operator=(TypePart&&)		= default;
	};

	#include "Refureku/TypeInfo/TypePart.inl"
}