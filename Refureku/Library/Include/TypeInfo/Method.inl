
template <typename... Args>
void Method::invoke(void* caller, Args&&... arguments) const noexcept
{
	//TODO Security check
}

/**
*	Invoke the method with the provided arguments if the return type and argument types match this method prototype
*/
template <typename ReturnType, typename... Args>
ReturnType Method::invoke(void* caller, Args&&... arguments) const noexcept
{
	//TODO
}

template <typename... Args>
void Method::safeInvoke(void* caller, Args&&... arguments) const noexcept
{
	//TODO
}

template <typename ReturnType, typename... Args>
ReturnType Method::safeInvoke(void* caller, Args&&... arguments) const noexcept
{
	//TODO
}