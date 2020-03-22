
template <typename ReturnType, typename... Args>
ReturnType Method::internalInvoke(void* caller, Args&&... arguments) const noexcept
{
	MemberFunction<DummyClass, ReturnType(Args...)>& method = *static_cast<MemberFunction<DummyClass, ReturnType(Args...)>*>(_internalMethod);
	method.setCaller(caller);

	return method(std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType Method::internalInvoke(void const* caller, Args&&... arguments) const noexcept
{
	MemberFunction<DummyClass, ReturnType(Args...)>& method = *static_cast<MemberFunction<DummyClass, ReturnType(Args...)>*>(_internalMethod);
	method.setCaller(caller);

	return method(std::forward<Args>(arguments)...);
}

template <typename... Args>
void Method::invoke(void* caller, Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	internalInvoke<void, Args...>(std::forward<void*>(caller), std::forward<Args>(arguments)...);
}

template <typename... Args>
void Method::invoke(void const* caller, Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)
	//TODO check nullptr

	#endif

	internalInvoke<void, Args...>(std::forward<void const*>(caller), std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType Method::invoke(void* caller, Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	return internalInvoke<ReturnType, Args...>(std::forward<void*>(caller), std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType Method::invoke(void const* caller, Args&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	//TODO Security check throw exception (inherit from std::runtime_error)

	#endif

	return internalInvoke<ReturnType, Args...>(std::forward<void const*>(caller), std::forward<Args>(arguments)...);
}

template <typename... Args>
void Method::safeInvoke(void* caller, Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	internalInvoke<void, Args...>(std::forward<void*>(caller), std::forward<Args>(arguments)...);
}

template <typename... Args>
void Method::safeInvoke(void const* caller, Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	internalInvoke<void, Args...>(std::forward<void const*>(caller), std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType Method::safeInvoke(void* caller, Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	return internalInvoke<ReturnType, Args...>(std::forward<void*>(caller), std::forward<Args>(arguments)...);
}

template <typename ReturnType, typename... Args>
ReturnType Method::safeInvoke(void const* caller, Args&&... arguments) const
{
	//TODO Security check throw exception (inherit from std::runtime_error)

	return internalInvoke<ReturnType, Args...>(std::forward<void const*>(caller), std::forward<Args>(arguments)...);
}