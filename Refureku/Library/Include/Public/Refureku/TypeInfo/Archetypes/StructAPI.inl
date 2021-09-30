/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
void* internal::defaultInstantiator()
{
	if constexpr (std::is_default_constructible_v<T>)
	{
		return new T();
	}
	else
	{
		return nullptr;
	}
}