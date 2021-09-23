/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...)>::hasSamePrototype(MethodBase const& method) noexcept
{
	return !method.isConst() && method.hasSamePrototype<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...) noexcept>::hasSamePrototype(MethodBase const& method) noexcept
{
	return !method.isConst() && method.hasSamePrototype<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...) const>::hasSamePrototype(MethodBase const& method) noexcept
{
	return method.isConst() && method.hasSamePrototype<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...) const noexcept>::hasSamePrototype(MethodBase const& method) noexcept
{
	return method.isConst() && method.hasSamePrototype<ReturnType, ArgTypes...>();
}