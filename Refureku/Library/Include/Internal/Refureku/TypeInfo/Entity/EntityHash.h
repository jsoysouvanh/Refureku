/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t

namespace rfk
{
	//Forward declaration
	class Entity;

	struct EntityNameHash
	{
		std::size_t operator()(Entity const& entity)	const;
	};

	struct EntityIdHash
	{
		std::size_t operator()(Entity const& entity)	const;
	};

	struct EntityNameEqual
	{
		bool operator()(Entity const& lhs,
						Entity const& rhs)	const;
	};

	struct EntityIdEqual
	{
		bool operator()(Entity const& lhs,
						Entity const& rhs)	const;
	};

	struct EntityPtrNameHash
	{
		std::size_t operator()(Entity const* entity) const;
	};

	struct EntityPtrIdHash
	{
		std::size_t operator()(Entity const* entity) const;
	};

	struct EntityPtrNameEqual
	{
		bool operator()(Entity const* lhs,
						Entity const* rhs)	const;
	};

	struct EntityPtrIdEqual
	{
		bool operator()(Entity const* lhs,
						Entity const* rhs)	const;
	};
}