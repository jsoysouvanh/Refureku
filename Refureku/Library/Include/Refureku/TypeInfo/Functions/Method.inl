/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::internalInvoke(void const* caller, ArgTypes&&... arguments) const noexcept
{
	return reinterpret_cast<MemberFunction<DummyClass, ReturnType(ArgTypes...)>*>(internalMethod.get())->operator()(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::invoke(void const* caller, ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount<ArgTypes...>();

	#endif

	internalInvoke<void, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::rInvoke(void const* caller, ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount<ArgTypes...>();

	#endif

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::checkedInvoke(void const* caller, ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	internalInvoke<void, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::checkedRInvoke(void const* caller, ArgTypes&&... arguments) const
{
	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}