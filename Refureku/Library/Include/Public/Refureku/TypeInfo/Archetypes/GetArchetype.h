/**
*	Copyright (c) 2021-2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::is_function_v, std::is_member_object_pointer_v, std::is_pointer_v...

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"	//rfk::getEnum
#include "Refureku/Misc/TypeTraits.h"

#define RFK_DEFINE_GET_ARCHETYPE_TEMPLATE(...) namespace rfk { template <template <__VA_ARGS__> typename> Archetype const* getArchetype() noexcept { return nullptr; } }

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
	Archetype const*				getArchetype()						noexcept;

	/**
	*	@brief	Get archetype for template classes. Cover only most common cases.
	* 
	*	@return The archetype of the provided type if it exists, else nullptr.
	*/
	template <template <typename...> typename T>
	Archetype const*				getArchetype()						noexcept;	//Variadic type template parameters

	template <template <auto...> typename T>
	Archetype const*				getArchetype()						noexcept;	//Variadic non-type template parameters

#if RFK_TEMPLATE_TEMPLATE_SUPPORT
	template <template <template <typename...> typename...> typename T>
	Archetype const*				getArchetype()						noexcept;	//Variadic template template type parameters
#endif

	/**
	*	rfk::getArchetype specialization for all fundamental types.
	*/
	template <>
	REFUREKU_API Archetype const* getArchetype<void>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<std::nullptr_t>()		noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<bool>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<char>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<signed char>()			noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<unsigned char>()			noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<wchar_t>()				noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<char16_t>()				noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<char32_t>()				noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<short>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<unsigned short>()		noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<int>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<unsigned int>()			noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<long>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<unsigned long>()			noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<long long>()				noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<unsigned long long>()	noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<float>()					noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<double>()				noexcept;

	template <>
	REFUREKU_API Archetype const* getArchetype<long double>()			noexcept;

	#include "Refureku/TypeInfo/Archetypes/GetArchetype.inl"
}