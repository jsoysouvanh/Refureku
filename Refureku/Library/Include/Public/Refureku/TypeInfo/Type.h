/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>		//std::size_t
#include <type_traits>	//std::is_const_v, std::is_volatile_v, std::is_array_v, ...

#include "Refureku/Misc/Pimpl.h"
#include "Refureku/TypeInfo/TypePart.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"

namespace rfk
{
	class Type
	{
		public:
			REFUREKU_API Type()		noexcept;
			Type(Type const&)		noexcept;
			Type(Type&&)			noexcept;
			REFUREKU_API ~Type()	noexcept;

			/**
			*	@brief	Get the type part at the specified index.
			*			If index is greater or equal to the type parts count, the behaviour is undefined.
			* 
			*	@param index Index of the part to get.
			* 
			*	@return The type part at the specified index.
			*/
			REFUREKU_API TypePart const&		getTypePartAt(std::size_t index)	const	noexcept;

			/**
			*	@brief Get the number of type parts constituting this type.
			* 
			*	@return The number of type parts constituting this type.
			*/
			REFUREKU_API std::size_t			getTypePartsCount()					const	noexcept;

			/**
			*	@return true if this type is a pointer type (*), else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isPointer()							const	noexcept;

			/**
			*	@return true if this type is a left value reference type (&), else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isLValueReference()					const	noexcept;

			/**
			*	@return true if this type is a right value reference type (&&), else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isRValueReference()					const	noexcept;

			/**
			*	@return true if this type is a c-style array ([]), else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isCArray()							const	noexcept;

			/**
			*	@return true if this type is a value type (not a pointer, lvalue ref, rvalue ref, c-style array), else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isValue()							const	noexcept;

			/**
			*	@return true if this type is const qualified, else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isConst()							const	noexcept;

			/**
			*	@return true if this type is volatile qualified, else false.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API bool					isVolatile()						const	noexcept;

			/**
			*	@return The size of the array if isCArray() is true, else 0.
			*			The behaviour is undefined if getTypePartsCount() returns 0.
			*/
			REFUREKU_API uint32					getCArraySize()						const	noexcept;

			/**
			*	@param other The other type to compare with.
			*
			*	@return true if two types match together if they represent the same type.
			*			Pointers and nullptr_t types also match together.
			*/
			REFUREKU_API bool					match(Type const& other)			const	noexcept;

			/**
			*	@brief Get this type's archetype.
			* 
			*	@return This type's archetype.
			*/
			REFUREKU_API Archetype const*		getArchetype()						const	noexcept;

			/**
			*	@brief Set this type's archetype.
			* 
			*	@param archetype The archetype to set.
			*/
			REFUREKU_API void					setArchetype(Archetype const* archetype)	noexcept;

			/**
			*	@brief Add a default-constructed type part to this type.
			* 
			*	@return The newly constructed type part.
			*/
			REFUREKU_API TypePart&				addTypePart()								noexcept;

			/**
			*	@brief Reallocate the underlying dynamic memory to use no more than needed.
			*/
			REFUREKU_API void					optimizeMemory()							noexcept;


			REFUREKU_API bool operator==(Type const&)	const	noexcept;
			REFUREKU_API bool operator!=(Type const&)	const	noexcept;

		protected:
			//Forward declaration
			class TypeImpl;

		private:
			/** Concrete implementation of the Type class. */
			Pimpl<TypeImpl> _pimpl;

			//The rfk::getType<T> method can access Type internal methods to fill the type
			template <typename T>
			friend Type const& getType() noexcept;

			/**
			*	@brief Fill the provided Type according to template type T.
			* 
			*	@param out_type The Type object to fill.
			*/
			template <typename T>
			static void	fillType(Type& out_type)	noexcept;
	};

	/**
	*	@brief	Retrieve the Type object from a given type.
	*			Identical types will return the same Type object (the returned object will have the same address in memory).
	* 
	*	@return The computed type.
	*/
	template <typename T>
	Type const& getType() noexcept;

	#include "Refureku/TypeInfo/Type.inl"

	/*
	*	Export getType<T> instantiations for all fundamental types so that their address is shared among all consumers
	*/
	template REFUREKU_API Type const& getType<void>()				noexcept;
	template REFUREKU_API Type const& getType<std::nullptr_t>()		noexcept;
	template REFUREKU_API Type const& getType<bool>()				noexcept;
	template REFUREKU_API Type const& getType<char>()				noexcept;
	template REFUREKU_API Type const& getType<signed char>()		noexcept;
	template REFUREKU_API Type const& getType<unsigned char>()		noexcept;
	template REFUREKU_API Type const& getType<wchar_t>()			noexcept;
	template REFUREKU_API Type const& getType<char16_t>()			noexcept;
	template REFUREKU_API Type const& getType<char32_t>()			noexcept;
	template REFUREKU_API Type const& getType<short>()				noexcept;
	template REFUREKU_API Type const& getType<unsigned short>()		noexcept;
	template REFUREKU_API Type const& getType<int>()				noexcept;
	template REFUREKU_API Type const& getType<unsigned int>()		noexcept;
	template REFUREKU_API Type const& getType<long>()				noexcept;
	template REFUREKU_API Type const& getType<unsigned long>()		noexcept;
	template REFUREKU_API Type const& getType<long long>()			noexcept;
	template REFUREKU_API Type const& getType<unsigned long long>()	noexcept;
	template REFUREKU_API Type const& getType<float>()				noexcept;
	template REFUREKU_API Type const& getType<double>()				noexcept;
	template REFUREKU_API Type const& getType<long double>()		noexcept;
}