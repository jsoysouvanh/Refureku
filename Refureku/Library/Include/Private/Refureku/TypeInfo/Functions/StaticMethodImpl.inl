/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline StaticMethod::StaticMethodImpl::StaticMethodImpl(char const* name, std::size_t id, Type const& returnType,
													ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBaseImpl(name, id, returnType, internalMethod, flags, outerEntity)
{
}