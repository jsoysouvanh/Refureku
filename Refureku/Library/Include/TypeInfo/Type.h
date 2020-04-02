#pragma once

#include <iostream>
#include <vector>

#include "TypeInfo/Archetypes/Archetype.h"
#include "TypeInfo/TypePart.h"

namespace rfk
{
	class Type
	{
		public:
			/** Archetype of this type */
			Archetype const*		archetype = nullptr;

			/** Parts of this type */
			std::vector<TypePart>	parts;

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= default;
			~Type()				= default;

			inline Type&	addPart(TypePart&& newPart)	noexcept;
			inline Type&	removePart()				noexcept;

			inline bool		isPointer()			const	noexcept;
			inline bool		isLValueReference()	const	noexcept;
			inline bool		isRValueReference()	const	noexcept;
			inline bool		isCArray()			const	noexcept;
			inline bool		isValue()			const	noexcept;
			inline bool		isConst()			const	noexcept;
			inline bool		isVolatile()		const	noexcept;
			inline uint32	getArraySize()		const	noexcept;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;

			bool operator==(Type const& type)	const noexcept;
	};

	#include "TypeInfo/Type.inl"

	std::ostream& operator<<(std::ostream& stream, Type const& type) noexcept;
}