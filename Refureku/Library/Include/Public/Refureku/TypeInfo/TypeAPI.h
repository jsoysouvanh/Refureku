/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cstddef>		//std::size_t
#include <type_traits>	//std::is_const_v, std::is_volatile_v, std::is_array_v, ...

#include "Refureku/Utility/Pimpl.h"
#include "Refureku/TypeInfo/TypePartAPI.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetypeAPI.h"

namespace rfk
{
	class TypeAPI
	{
		public:
			REFUREKU_API TypeAPI()	noexcept;
			TypeAPI(TypeAPI const&)	noexcept;
			TypeAPI(TypeAPI&&)		noexcept;
			REFUREKU_API ~TypeAPI()	noexcept;

			/**
			*	@brief Add a default-constructed type part to this type.
			* 
			*	@return The newly constructed type part.
			*/
			REFUREKU_API TypePartAPI&			addTypePart()								noexcept;

			/**
			*	@brief Reallocate the underlying dynamic memory to use no more than needed.
			*/
			REFUREKU_API void					optimizeMemory()							noexcept;

			/**
			*	@brief	Get the type part at the specified index.
			*			If index is greater or equal to the type parts count, the behaviour is undefined.
			* 
			*	@param index Index of the part to get.
			* 
			*	@return The type part at the specified index.
			*/
			REFUREKU_API TypePartAPI const&		getTypePartAt(std::size_t index)	const	noexcept;

			/**
			*	@brief Get the number of type parts constituting this type.
			* 
			*	@return The number of type parts constituting this type.
			*/
			REFUREKU_API std::size_t			getTypePartsCount()					const	noexcept;

			/**
			*	@return true if this type is a pointer type (*), else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isPointer()							const	noexcept;

			/**
			*	@return true if this type is a left value reference type (&), else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isLValueReference()					const	noexcept;

			/**
			*	@return true if this type is a right value reference type (&&), else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isRValueReference()					const	noexcept;

			/**
			*	@return true if this type is a c-style array ([]), else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isCArray()							const	noexcept;

			/**
			*	@return true if this type is a value type (not a pointer, lvalue ref, rvalue ref, c-style array), else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isValue()							const	noexcept;

			/**
			*	@return true if this type is const qualified, else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isConst()							const	noexcept;

			/**
			*	@return true if this type is volatile qualified, else false.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API bool					isVolatile()						const	noexcept;

			/**
			*	@return The size of the array if isCArray() is true, else 0.
			*			The behaviour is undefined if type parts count is 0.
			*/
			REFUREKU_API uint32					getCArraySize()						const	noexcept;

			/**
			*	@param other The other type to compare with.
			*
			*	@return true if two types match together if they represent the same type.
			*			Pointers and nullptr_t types also match together.
			*/
			REFUREKU_API bool					match(TypeAPI const& other)			const	noexcept;

			/**
			*	@brief Get this type's archetype.
			* 
			*	@return This type's archetype.
			*/
			REFUREKU_API ArchetypeAPI const*	getArchetype()						const	noexcept;

			/**
			*	@brief Set this type's archetype.
			* 
			*	@param archetype The archetype to set.
			*/
			REFUREKU_API void					setArchetype(ArchetypeAPI const* archetype)	noexcept;


			REFUREKU_API bool operator==(TypeAPI const&)		const	noexcept;
			REFUREKU_API bool operator!=(TypeAPI const&)		const	noexcept;

		protected:
			//Forward declaration
			class TypeImpl;

		private:
			/** Concrete implementation of the Type class. */
			Pimpl<TypeImpl> _pimpl;

			//The rfk::getTypeAPI<T> method can access Type internal methods to fill the type
			template <typename T>
			friend TypeAPI const& getTypeAPI() noexcept;

			/**
			*	@brief Fill the provided TypeAPI according to template type T.
			* 
			*	@param out_type The Type object to fill.
			*/
			template <typename T>
			static void		fillType(TypeAPI& out_type)	noexcept;
	};

	/**
	*	@brief	Retrieve the Type object from a given type.
	*			Identical types will return the same Type object (the returned object will have the same address in memory).
	* 
	*	@return The computed type.
	*/
	//TODO: Replace this by getType
	template <typename T>
	TypeAPI const& getTypeAPI() noexcept;

	#include "Refureku/TypeInfo/TypeAPI.inl"

	/*
	*	Export getType<T> instantiations for all fundamental types so that their address is shared among all consumers
	*/
	template REFUREKU_API TypeAPI const& getTypeAPI<void>()					noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<std::nullptr_t>()		noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<bool>()					noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<char>()					noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<signed char>()			noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<unsigned char>()		noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<wchar_t>()				noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<char16_t>()				noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<char32_t>()				noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<short>()				noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<unsigned short>()		noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<int>()					noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<unsigned int>()			noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<long>()					noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<unsigned long>()		noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<long long>()			noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<unsigned long long>()	noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<float>()				noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<double>()				noexcept;
	template REFUREKU_API TypeAPI const& getTypeAPI<long double>()			noexcept;
}