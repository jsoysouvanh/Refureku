/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "TypeInfo/Entity.h"
#include "TypeInfo/Archetypes/Class.h"
#include "TypeInfo/Archetypes/Enum.h"

namespace rfk
{
	class Namespace final : public Entity
	{
		public:
			/** Collection of all namespaces contained in this namespace. */
			std::unordered_set<Namespace const*, Entity::PtrNameHasher, Entity::PtrEqualName>	nestedNamespaces;

			/** Collection of all archetypes contained in this namespace. */
			std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>	nestedArchetypes;

			Namespace(std::string&& newName,
					  uint64		newId	= 0u)	noexcept;
			Namespace(Namespace const&)				= delete;
			Namespace(Namespace&&)					= default;
			~Namespace()							= default;

			Namespace& operator=(Namespace const&)	= delete;
			Namespace& operator=(Namespace&&)		= default;
	};
}