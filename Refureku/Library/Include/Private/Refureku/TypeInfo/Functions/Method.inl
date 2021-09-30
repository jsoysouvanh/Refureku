/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::internalInvoke(CallerType& caller, ArgTypes&&... arguments) const noexcept
{
	return reinterpret_cast<MemberFunction<CallerType, ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::internalInvoke(CallerType const& caller, ArgTypes&&... arguments) const
{
	if (!isConst())
	{
		throw ConstViolation("Can't call a non-const member function on a const caller instance.");
	}

	return reinterpret_cast<MemberFunction<CallerType, ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename CallerType, typename... ArgTypes>
void Method::invoke(CallerType& caller, ArgTypes&&... arguments) const noexcept(RFK_RELEASE)
{
#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	internalInvoke<void, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename CallerType, typename... ArgTypes>
void Method::invoke(CallerType const& caller, ArgTypes&&... arguments) const
{
#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	internalInvoke<void, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::rInvoke(CallerType& caller, ArgTypes&&... arguments) const noexcept(RFK_RELEASE)
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	return internalInvoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::rInvoke(CallerType const& caller, ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

#if RFK_DEBUG

	checkArgumentsCount<ArgTypes...>();

#endif

	return internalInvoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename CallerType, typename... ArgTypes>
void Method::checkedInvoke(CallerType& caller, ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	internalInvoke<void, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename CallerType, typename... ArgTypes>
void Method::checkedInvoke(CallerType const& caller, ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	internalInvoke<void, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::checkedRInvoke(CallerType& caller, ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return internalInvoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::checkedRInvoke(CallerType const& caller, ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return internalInvoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(arguments)...);
}