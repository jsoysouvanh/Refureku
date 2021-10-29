/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline Variable::VariableImpl::VariableImpl(char const* name, std::size_t id, Type const& type, void* ptr, EVarFlags flags) noexcept:
	VariableBaseImpl(name, id, EEntityKind::Variable, type, nullptr),
	_flags{flags},
	_ptr{ptr}
{
}

inline Variable::VariableImpl::VariableImpl(char const* name, std::size_t id, Type const& type, void const* constPtr, EVarFlags flags) noexcept:
	VariableBaseImpl(name, id, EEntityKind::Variable, type, nullptr),
	_flags{flags},
	_constPtr{constPtr}
{
}

inline EVarFlags Variable::VariableImpl::getFlags() const noexcept
{
	return _flags;
}

inline void* Variable::VariableImpl::getPtr() const noexcept
{
	return _ptr;
}

inline void const* Variable::VariableImpl::getConstPtr() const noexcept
{
	return _constPtr;
}