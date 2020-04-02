#pragma once

#include "Misc/FundamentalTypes.h"
#include "Utility/EnumMacros.h"

namespace rfk
{
	enum class ETypePart : uint16
	{
		/** Default uninitialized value for this enum */
		Undefined	= 0,

		/** Keywords */
		Const		= 1 << 0,	
		Restrict	= 1 << 1,
		Volatile	= 1 << 2,

		/** Ptr/Ref/Array */
		Ptr			= 1 << 3,
		LRef		= 1 << 4,
		RRef		= 1 << 5,
		CArray		= 1 << 6,
		Value		= 1 << 7	//Means non-ptr simple value, ex: int
	};

	GENERATE_ENUM_OPERATORS(ETypePart);

	struct TypePart
	{
		uint16		padding			= 0u;

		ETypePart	part			= ETypePart::Undefined;
			
		uint32		additionalData	= 0u;
	};
}