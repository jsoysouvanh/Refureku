/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t

namespace rfk
{
	//Forward declaration
	class EntityAPI;

	struct EntityNameHash
	{
		std::size_t operator()(EntityAPI const& entity)	const;
	};

	struct EntityIdHash
	{
		std::size_t operator()(EntityAPI const& entity)	const;
	};

	struct EntityNameEqual
	{
		bool operator()(EntityAPI const& lhs,
						EntityAPI const& rhs)	const;
	};

	struct EntityIdEqual
	{
		bool operator()(EntityAPI const& lhs,
						EntityAPI const& rhs)	const;
	};

	struct EntityPtrNameHash
	{
		std::size_t operator()(EntityAPI const* entity) const;
	};

	struct EntityPtrIdHash
	{
		std::size_t operator()(EntityAPI const* entity) const;
	};

	struct EntityPtrNameEqual
	{
		bool operator()(EntityAPI const* lhs,
						EntityAPI const* rhs)	const;
	};

	struct EntityPtrIdEqual
	{
		bool operator()(EntityAPI const* lhs,
						EntityAPI const* rhs)	const;
	};
}