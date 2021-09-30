/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline StaticMethodAPI::StaticMethodImpl::StaticMethodImpl(char const* name, std::size_t id, TypeAPI const& returnType,
													ICallable* internalMethod, EMethodFlags flags, EntityAPI const* outerEntity) noexcept:
	MethodBaseImpl(name, id, returnType, internalMethod, flags, outerEntity)
{
}