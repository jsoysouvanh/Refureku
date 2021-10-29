/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...)>::hasSameSignature(MethodBase const& method) noexcept
{
	return !method.isConst() && method.hasSameSignature<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...) noexcept>::hasSameSignature(MethodBase const& method) noexcept
{
	return !method.isConst() && method.hasSameSignature<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...) const>::hasSameSignature(MethodBase const& method) noexcept
{
	return method.isConst() && method.hasSameSignature<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool MethodHelper<ReturnType(ArgTypes...) const noexcept>::hasSameSignature(MethodBase const& method) noexcept
{
	return method.isConst() && method.hasSameSignature<ReturnType, ArgTypes...>();
}