/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename... ArgTypes>
void StaticMethod::invoke(ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount<ArgTypes...>();

	#endif

	std::static_pointer_cast<NonMemberFunction<void(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::invoke(ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount<ArgTypes...>();

	#endif

	return std::static_pointer_cast<NonMemberFunction<ReturnType(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void StaticMethod::checkedInvoke(ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	std::static_pointer_cast<NonMemberFunction<void(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::checkedInvoke(ArgTypes&&... arguments) const
{
	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return std::static_pointer_cast<NonMemberFunction<ReturnType(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}