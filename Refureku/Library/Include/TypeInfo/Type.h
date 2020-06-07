/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

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
			static void				fillType(Type& out_type)	noexcept;

			template <typename T>
			static Archetype const* getArchetype() noexcept;

		public:
			/** Archetype of this type. */
			Archetype const*		archetype = nullptr;

			/** Parts of this type. */
			std::vector<TypePart>	parts;

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= default;
			~Type()				= default;

			/**
			*	Retrieve the Type object from a given type.
			*	Identical types will return the same Type object (the returned object will have the same address in memory).
			*/
			template <typename T>
			static Type const&	getType()							noexcept;

			/**
			*	Add multiple type parts to this type object at once.
			*
			*	\tparam ArgTypes Type of the argument, must actually be TypePart.
			*
			*	\param args Multiple instances of TypePart.
			*
			*	\return A reference to the modified Type (this).
			*/
			template <typename... ArgTypes>
			inline Type&		addPart(ArgTypes&&... args)			noexcept;

			/**
			*	Add a TypePart to this type instance.
			*
			*	\param newPart The part to add to this type.
			*
			*	\return A reference to the modified Type (this).
			*/
			inline Type&		addPart(TypePart const&	newPart)	noexcept;

			/**
			*	Remove the last TypePart from this type instance.
			*
			*	\return A reference to the modified Type (this).
			*/
			inline Type&		removePart()						noexcept;

			/** 
			*	\return true if this type is a pointer type (*), else false.
			*/
			inline bool			isPointer()					const	noexcept;

			/**
			*	\return true if this type is a left value reference type (&), else false.
			*/
			inline bool			isLValueReference()			const	noexcept;

			/**
			*	\return true if this type is a right value reference type (&&), else false.
			*/
			inline bool			isRValueReference()			const	noexcept;

			/**
			*	\return true if this type is a c-style array ([]), else false.
			*/
			inline bool			isCArray()					const	noexcept;

			/**
			*	\return true if this type is a value type (not a pointer, lvalue ref, rvalue ref, c-style array), else false.
			*/
			inline bool			isValue()					const	noexcept;

			/**
			*	\return true if this type is const qualified, else false.
			*/
			inline bool			isConst()					const	noexcept;

			/**
			*	\return true if this type is volatile qualified, else false.
			*/
			inline bool			isVolatile()				const	noexcept;

			/**
			*	\return The size of the array if isCArray() returns true, else 0.
			*/
			inline uint32		getArraySize()				const	noexcept;

			/**
			*	\param type The other type to compare with.
			*
			*	\return true if two types match together if they represent the same type.
			*			Pointers and nullptr_t types also match together.
			*/
			bool				match(Type const& type)		const	noexcept;

			/**
			*	\return a string representation of the content of this type.
			*/
			std::string			toString()					const	noexcept;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;

			bool operator==(Type const& type)	const noexcept;
			bool operator!=(Type const& type)	const noexcept;
	};

	#include "TypeInfo/Type.inl"

	std::ostream& operator<<(std::ostream& stream, Type const& type) noexcept;
}