#pragma once

#include <type_traits>

#include "Misc/FundamentalTypes.h"
#include "Utility/EnumMacros.h"

namespace rfk
{
	enum class ETypePartDescriptor : uint16
	{
		/** Default uninitialized value for this enum */
		Undefined	= 0,

		/** Keywords */
		Const		= 1 << 0,	
		//Restrict	= 1 << 1,
		Volatile	= 1 << 2,

		/** Ptr/Ref/Array */
		Ptr			= 1 << 3,
		LRef		= 1 << 4,
		RRef		= 1 << 5,
		CArray		= 1 << 6,
		Value		= 1 << 7	//Means non-ptr simple value, ex: int
	};

	GENERATE_ENUM_OPERATORS(ETypePartDescriptor);

	class TypePart
	{
		public:
			/** Align memory so that Type part is exactly 64 bits */
			uint16				padding			= 0u;
			
			/** Actual data describing this type part */
			ETypePartDescriptor	descriptor		= ETypePartDescriptor::Undefined;
			
			/** Some additional data which might complement descriptor (for example CArray size) */
			uint32				additionalData	= 0u;

			TypePart()																		= default;
			TypePart(uint16 padding, ETypePartDescriptor descriptor, uint32 additionalData)	noexcept;
			TypePart(TypePart const&)														= default;
			TypePart(TypePart&&)															= default;
			~TypePart()																		= default;

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

	#include "TypeInfo/TypePart.inl"
}