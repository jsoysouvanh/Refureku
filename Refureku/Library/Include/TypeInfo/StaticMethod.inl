
template <typename... Args>
void StaticMethod::invoke(Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	std::static_pointer_cast<NonMemberFunction<void(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::invoke(Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	return std::static_pointer_cast<NonMemberFunction<ReturnType(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}

template <typename... Args>
void StaticMethod::safeInvoke(Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	std::static_pointer_cast<NonMemberFunction<void(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::safeInvoke(Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	return std::static_pointer_cast<NonMemberFunction<ReturnType(Args...)>>(_internalMethod)->operator()(std::forward<Args>(arguments)...);
}