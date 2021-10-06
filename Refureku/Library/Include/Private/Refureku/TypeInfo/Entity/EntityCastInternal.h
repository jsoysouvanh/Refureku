/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"

namespace rfk
{
	/**
	*	@brief Helper function to cast simple entity types.
	*
	*	@tparam T Concrete type to cast to.
	*
	*	@param entity The entity to cast.
	*	
	*	@return The casted entity if the entity concrete type was correct, else nullptr.
	*/
	template <typename T, EEntityKind CheckKind>
	T const* entityCast(Entity const* entity) noexcept;

	#include "Refureku/TypeInfo/Entity/EntityCastInternal.inl"
}