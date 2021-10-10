/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline Function::FunctionImpl::FunctionImpl(char const* name, std::size_t id,
											   Type const& returnType, ICallable* internalFunction, EFunctionFlags flags) noexcept:
	FunctionBaseImpl(name, id, EEntityKind::Function, returnType, internalFunction, nullptr),
	_flags{flags}
{
}

inline EFunctionFlags Function::FunctionImpl::getFlags() const noexcept
{
	return _flags;
}