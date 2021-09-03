/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename CallerType, typename ReturnType, typename... ArgTypes>
MemberFunction<CallerType, ReturnType(ArgTypes...)>::MemberFunction(FunctionPrototype function) noexcept:
	_function{function},
	_isConst{false}
{}

template <typename CallerType, typename ReturnType, typename... ArgTypes>
MemberFunction<CallerType, ReturnType(ArgTypes...)>::MemberFunction(ConstFunctionPrototype function) noexcept:
	_constFunction{function},
	_isConst{true}
{}

template <typename CallerType, typename ReturnType, typename... ArgTypes>
ReturnType MemberFunction<CallerType, ReturnType(ArgTypes...)>::operator()(void* caller, ArgTypes&&... args) const
{
	return _isConst ?	(reinterpret_cast<CallerType*>(caller)->*_constFunction)(std::forward<ArgTypes>(args)...) :
						(reinterpret_cast<CallerType*>(caller)->*_function)(std::forward<ArgTypes>(args)...);
}

template <typename CallerType, typename ReturnType, typename... ArgTypes>
ReturnType MemberFunction<CallerType, ReturnType(ArgTypes...)>::operator()(void const* caller, ArgTypes&&... args) const
{
	if (!_isConst)
	{
		throw ConstViolation("Can't call a non-const member function on a const caller instance.");
	}

	return (reinterpret_cast<CallerType const*>(caller)->*_constFunction)(std::forward<ArgTypes>(args)...);
}