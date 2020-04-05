
template <typename ReturnType, typename... ArgTypes>
ReturnType Method::internalInvoke(void const* caller, ArgTypes&&... arguments) const noexcept
{
	return std::static_pointer_cast<MemberFunction<DummyClass, ReturnType(ArgTypes...)>>(_internalMethod)->operator()(caller, std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::invoke(void const* caller, ArgTypes&&... arguments) const noexcept
{
	internalInvoke<void, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::invoke(void const* caller, ArgTypes&&... arguments) const noexcept
{
	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Method::safeInvoke(void const* caller, ArgTypes&&... arguments) const
{
	checkArguments(std::forward<ArgTypes>(arguments)...);

	internalInvoke<void, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::safeInvoke(void const* caller, ArgTypes&&... arguments) const
{
	checkReturnType<ReturnType>();
	checkArguments(std::forward<ArgTypes>(arguments)...);

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<void const*>(caller), std::forward<ArgTypes>(arguments)...);
}