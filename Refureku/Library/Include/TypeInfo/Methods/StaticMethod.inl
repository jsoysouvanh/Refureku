
template <typename... Args>
void StaticMethod::invoke(Args&&... arguments) const noexcept
{
	std::static_pointer_cast<NonMemberFunction<void(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::invoke(Args&&... arguments) const noexcept
{
	return std::static_pointer_cast<NonMemberFunction<ReturnType(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}

template <typename... Args>
void StaticMethod::safeInvoke(Args&&... arguments) const
{
	checkArguments(std::forward<Args>(arguments)...);

	std::static_pointer_cast<NonMemberFunction<void(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::safeInvoke(Args&&... arguments) const
{
	checkReturnType<ReturnType>();
	checkArguments(std::forward<Args>(arguments)...);

	return std::static_pointer_cast<NonMemberFunction<ReturnType(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}