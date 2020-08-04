/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Entity.h"

namespace rfk
{
	class NamespaceFragment final : public Entity
	{
		public:
			/** Collection of all entities contained in this namespace fragment. */
			std::vector<Entity const*>	nestedEntities;

			NamespaceFragment(std::string&& newName,
							  uint64		newId	= 0u)	noexcept;
			NamespaceFragment(NamespaceFragment const&)		= delete;
			NamespaceFragment(NamespaceFragment&&)			= default;
			~NamespaceFragment()							= default;
	};
}