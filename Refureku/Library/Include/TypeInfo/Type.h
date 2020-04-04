#pragma once

#include <iostream>
#include <vector>
#include <type_traits>

#include "Utility/TypeTraits.h"
#include "TypeInfo/TypePart.h"
#include "TypeInfo/Archetypes/FundamentalArchetypes.h"
#include "TypeInfo/Archetypes/Enum.h"

namespace rfk
{
	class Type
	{
		private:
			template <typename T>
			static constexpr void	fillType(Type& out_type)	noexcept;

			template <typename T>
			static Archetype const* getArchetype() noexcept;

		public:
			/** Archetype of this type */
			Archetype const*		archetype = nullptr;

			/** Parts of this type */
			std::vector<TypePart>	parts;

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= default;
			~Type()				= default;

			template <typename T>
			static Type const&	getType()							noexcept;

			template <typename... ArgTypes>
			inline Type&		addPart(ArgTypes&&...	args)		noexcept;

			inline Type&		addPart(TypePart const&	newPart)	noexcept;
			inline Type&		removePart()						noexcept;

			inline bool			isPointer()					const	noexcept;
			inline bool			isLValueReference()			const	noexcept;
			inline bool			isRValueReference()			const	noexcept;
			inline bool			isCArray()					const	noexcept;
			inline bool			isValue()					const	noexcept;
			inline bool			isConst()					const	noexcept;
			inline bool			isVolatile()				const	noexcept;
			inline uint32		getArraySize()				const	noexcept;

			std::string			toString()					const	noexcept;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;

			bool operator==(Type const& type)	const noexcept;
			bool operator!=(Type const& type)	const noexcept;
	};

	#include "TypeInfo/Type.inl"

	std::ostream& operator<<(std::ostream& stream, Type const& type) noexcept;
}