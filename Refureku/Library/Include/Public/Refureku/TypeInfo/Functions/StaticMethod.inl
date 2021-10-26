/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::internalInvoke(ArgTypes&&... args) const
{
	return reinterpret_cast<NonMemberFunction<ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::invoke(ArgTypes&&... args) const
{
	return internalInvoke<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::checkedInvoke(ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();

	return invoke<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
}