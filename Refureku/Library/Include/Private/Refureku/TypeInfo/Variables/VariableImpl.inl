/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline VariableAPI::VariableImpl::VariableImpl(char const* name, std::size_t id, TypeAPI const& type, void* ptr, EVarFlags flags) noexcept:
	VariableBaseImpl(name, id, EEntityKind::Variable, type, nullptr),
	_flags{flags},
	_ptr{ptr}
{
}

inline VariableAPI::VariableImpl::VariableImpl(char const* name, std::size_t id, TypeAPI const& type, void const* constPtr, EVarFlags flags) noexcept:
	VariableBaseImpl(name, id, EEntityKind::Variable, type, nullptr),
	_flags{flags},
	_constPtr{constPtr}
{
}

inline EVarFlags VariableAPI::VariableImpl::getFlags() const noexcept
{
	return _flags;
}

inline void* VariableAPI::VariableImpl::getPtr() const noexcept
{
	return _ptr;
}

inline void const* VariableAPI::VariableImpl::getConstPtr() const noexcept
{
	return _constPtr;
}