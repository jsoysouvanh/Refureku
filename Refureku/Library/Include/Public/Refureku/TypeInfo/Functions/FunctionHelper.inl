/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
bool FunctionHelper<ReturnType(ArgTypes...)>::hasSamePrototype(FunctionAPI const& function) noexcept
{
	return function.hasSamePrototype<ReturnType, ArgTypes...>();
}

template <typename ReturnType, typename... ArgTypes>
bool FunctionHelper<ReturnType(ArgTypes...) noexcept>::hasSamePrototype(FunctionAPI const& function) noexcept
{
	return function.hasSamePrototype<ReturnType, ArgTypes...>();
}