/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/TypeInfo/Archetypes/Enum.h"

namespace rfk
{
	/**
	*	@brief	Get the archetype of any type if it exists.
	*			Note that this method will always return nullptr on protected/private nested archetypes.
	*			If a cv-qualified, pointer/reference, array type is passed, they are all ignored and the raw type archetype is returned.
	*			Example:	int* -> int,
	*						int[2] -> int,
	*						const volatile int -> int,
	*						int& -> int
	*
	*			This templated method can be specialized to handle unreflected types.
	*
	*	@return The archetype of the provided type if it exists, else nullptr.
	*/
	template <typename T>
	Archetype const* getArchetype()	noexcept;

	/**
	*	@brief	Get archetype for template classes. Cover only most common cases.
	* 
	*	@return The archetype of the provided type if it exists, else nullptr.
	*/
	template <template <typename...> typename T>
	Archetype const* getArchetype()	noexcept;								//Variadic type template parameters

	template <template <auto...> typename T>
	Archetype const* getArchetype()	noexcept;								//Variadic non-type template parameters

	template <template <template <typename...> typename...> typename T>
	Archetype const* getArchetype()	noexcept;								//Variadic template template type parameters

	template <template <typename, auto> typename T>
	Archetype const* getArchetype()	noexcept;

	/**
	*	rfk::getArchetype specialization for all fundamental types.
	*/
	template <>
	Archetype const* getArchetype<void>()				noexcept;

	template <>
	Archetype const* getArchetype<std::nullptr_t>()		noexcept;

	template <>
	Archetype const* getArchetype<bool>()				noexcept;

	template <>
	Archetype const* getArchetype<char>()				noexcept;

	template <>
	Archetype const* getArchetype<signed char>()		noexcept;

	template <>
	Archetype const* getArchetype<unsigned char>()		noexcept;

	template <>
	Archetype const* getArchetype<wchar_t>()			noexcept;

	template <>
	Archetype const* getArchetype<char16_t>()			noexcept;

	template <>
	Archetype const* getArchetype<char32_t>()			noexcept;

	template <>
	Archetype const* getArchetype<short>()				noexcept;

	template <>
	Archetype const* getArchetype<unsigned short>()		noexcept;

	template <>
	Archetype const* getArchetype<int>()				noexcept;

	template <>
	Archetype const* getArchetype<unsigned int>()		noexcept;

	template <>
	Archetype const* getArchetype<long>()				noexcept;

	template <>
	Archetype const* getArchetype<unsigned long>()		noexcept;

	template <>
	Archetype const* getArchetype<long long>()			noexcept;

	template <>
	Archetype const* getArchetype<unsigned long long>()	noexcept;

	template <>
	Archetype const* getArchetype<float>()				noexcept;

	template <>
	Archetype const* getArchetype<double>()				noexcept;

	template <>
	Archetype const* getArchetype<long double>()		noexcept;

	#include "Refureku/TypeInfo/Archetypes/GetArchetype.inl"
}