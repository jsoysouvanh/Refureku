/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::internalInvoke(void* caller, ArgTypes&&... arguments) const noexcept
{
	return reinterpret_cast<MemberFunction<DummyClass, ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::internalInvoke(void const* caller, ArgTypes&&... arguments) const
{
	return reinterpret_cast<MemberFunction<DummyClass, ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::invoke(void* caller, ArgTypes&&... arguments) const noexcept(RFK_RELEASE)
{
#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	internalInvoke<void, ArgTypes...>(std::forward<void*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::invoke(void const* caller, ArgTypes&&... arguments) const
{
#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	internalInvoke<void, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::rInvoke(void* caller, ArgTypes&&... arguments) const noexcept(RFK_RELEASE)
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::rInvoke(void const* caller, ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::checkedInvoke(void* caller, ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	internalInvoke<void, ArgTypes...>(std::forward<void*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::checkedInvoke(void const* caller, ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	internalInvoke<void, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::checkedRInvoke(void* caller, ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::checkedRInvoke(void const* caller, ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}