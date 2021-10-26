/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
template <typename Functor>
NonMemberFunction<ReturnType(ArgTypes...)>::NonMemberFunction(Functor f) noexcept:
	_function{static_cast<FunctionPrototype>(f)}
{
}

template <typename ReturnType, typename... ArgTypes>
NonMemberFunction<ReturnType(ArgTypes...)>::NonMemberFunction(FunctionPrototype function) noexcept:
	_function{function}
{
}

template <typename ReturnType, typename... ArgTypes>
typename NonMemberFunction<ReturnType(ArgTypes...)>::FunctionPrototype NonMemberFunction<ReturnType(ArgTypes...)>::getFunctionHandle() const noexcept
{
	return _function;
}

template <typename ReturnType, typename... ArgTypes>
ReturnType NonMemberFunction<ReturnType(ArgTypes...)>::operator()(ArgTypes&&... args) const
{
	return _function(std::forward<ArgTypes>(args)...);
}