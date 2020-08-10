/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

namespace kodgen
{
	/**
	*	Enum representing type of an entity
	*	This avoids unnecessary dynamic casts and allows EntityInfo to be a non-polymorphic class
	*/
	enum class EEntityType : uint16
	{
		/** Unset type. */
		Undefined	= 0u,

		/** class. */
		Class		= 1 << 0,

		/** struct. */
		Struct		= 1 << 1,

		/** enum or enum class. */
		Enum		= 1 << 2,

		/** Non-member variable. */
		Variable	= 1 << 3,

		/** Member-variable. */
		Field		= 1 << 4,

		/** Non-member function. */
		Function	= 1 << 5,

		/** Member-function. */
		Method		= 1 << 6,

		/** enum value or enum class value. */
		EnumValue	= 1 << 7,

		/** namespace. */
		Namespace	= 1 << 8
	};

	inline EEntityType operator|(EEntityType flags1, EEntityType flags2)
	{
		using UnderlyingType = std::underlying_type_t<EEntityType>;

		return static_cast<EEntityType>(static_cast<UnderlyingType>(flags1) | static_cast<UnderlyingType>(flags2));
	}

	inline EEntityType operator&(EEntityType flags1, EEntityType flags2)
	{
		using UnderlyingType = std::underlying_type_t<EEntityType>;

		return static_cast<EEntityType>(static_cast<UnderlyingType>(flags1) & static_cast<UnderlyingType>(flags2));
	}
}