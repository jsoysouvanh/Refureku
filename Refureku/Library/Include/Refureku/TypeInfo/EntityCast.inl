/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T, Entity::EKind CheckKind, typename>
T const* rfk::internal::entityCast(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->kind == CheckKind) ? reinterpret_cast<T const*>(entity) : nullptr;
}