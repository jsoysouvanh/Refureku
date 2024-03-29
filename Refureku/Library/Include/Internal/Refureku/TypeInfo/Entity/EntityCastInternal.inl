/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename T, EEntityKind CheckKind>
T const* entityCast(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == CheckKind) ? reinterpret_cast<T const*>(entity) : nullptr;
}