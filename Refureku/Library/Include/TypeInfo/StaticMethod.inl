
template <typename... Args>
void StaticMethod::invoke(Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	(*static_cast<NonMemberFunction<void(Args...)>*>(_internalMethod))(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::invoke(Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	return (*static_cast<NonMemberFunction<ReturnType(Args...)>*>(_internalMethod))(std::forward<Args>(arguments)...);
}

template <typename... Args>
void StaticMethod::safeInvoke(Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	(*static_cast<NonMemberFunction<void(Args...)>*>(_internalMethod))(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::safeInvoke(Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	return (*static_cast<NonMemberFunction<ReturnType(Args...)>*>(_internalMethod))(std::forward<Args>(arguments)...);
}