/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
bool FunctionHelper<ReturnType(ArgTypes...)>::hasSameSignature(Function const& function) noexcept
{
	return function.hasSameSignature<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool FunctionHelper<ReturnType(ArgTypes...) noexcept>::hasSameSignature(Function const& function) noexcept
{
	return function.hasSameSignature<ReturnType, ArgTypes...>();
}