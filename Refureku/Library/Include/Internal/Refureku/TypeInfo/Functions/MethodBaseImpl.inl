/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline MethodBase::MethodBaseImpl::MethodBaseImpl(char const* name, std::size_t id, Type const& returnType,
													 ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	FunctionBaseImpl(name, id, EEntityKind::Method, returnType, internalMethod, outerEntity),
	_flags{flags}
{
}

inline EMethodFlags MethodBase::MethodBaseImpl::getFlags() const noexcept
{
	return _flags;
}