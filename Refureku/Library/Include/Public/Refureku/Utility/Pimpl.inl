/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
template <typename... Args>
Pimpl<T>::Pimpl(Args&&... arguments):
	_implReference(std::forward<Args>(arguments)...)
{
}

template <typename T>
T& Pimpl<T>::get() noexcept
{
	return _implReference;
}

template <typename T>
T const& Pimpl<T>::get() const noexcept
{
	return _implReference;
}

template <typename T>
T& Pimpl<T>::operator->() noexcept
{
	return _implReference;
}

template <typename T>
T const& Pimpl<T>::operator->() const noexcept
{
	return _implReference;
}