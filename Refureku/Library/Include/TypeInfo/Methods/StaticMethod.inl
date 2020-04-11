
template <typename... ArgTypes>
void StaticMethod::invoke(ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount(std::forward<ArgTypes>(arguments)...);

	#endif

	std::static_pointer_cast<NonMemberFunction<void(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::invoke(ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount(std::forward<ArgTypes>(arguments)...);

	#endif

	return std::static_pointer_cast<NonMemberFunction<ReturnType(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void StaticMethod::checkedInvoke(ArgTypes&&... arguments) const
{
	checkArguments(std::forward<ArgTypes>(arguments)...);

	std::static_pointer_cast<NonMemberFunction<void(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethod::checkedInvoke(ArgTypes&&... arguments) const
{
	checkReturnType<ReturnType>();
	checkArguments(std::forward<ArgTypes>(arguments)...);

	return std::static_pointer_cast<NonMemberFunction<ReturnType(ArgTypes...)>>(_internalMethod)->operator()(std::forward<ArgTypes>(arguments)...);
}