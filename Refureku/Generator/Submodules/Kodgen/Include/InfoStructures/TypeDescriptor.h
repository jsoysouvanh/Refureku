#pragma once

#include <type_traits>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	enum ETypeDescriptor : uint16
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

	inline ETypeDescriptor operator|(ETypeDescriptor e1, ETypeDescriptor e2) noexcept
	{
		using UnderlyingType = std::underlying_type_t<ETypeDescriptor>;

		return static_cast<ETypeDescriptor>(static_cast<UnderlyingType>(e1) | static_cast<UnderlyingType>(e2));
	}

	inline ETypeDescriptor operator&(ETypeDescriptor e1, ETypeDescriptor e2) noexcept
	{
		using UnderlyingType = std::underlying_type_t<ETypeDescriptor>;

		return static_cast<ETypeDescriptor>(static_cast<UnderlyingType>(e1) & static_cast<UnderlyingType>(e2));
	}

	struct TypePart
	{
		uint16			padding;

		ETypeDescriptor	descriptor;

		/** If descriptor is a CArray, additionalData is size. Might contain other information in other cases. */
		uint32			additionalData;
	};

	static_assert(sizeof(TypePart) == sizeof(uint64));
}