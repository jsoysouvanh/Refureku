
template <typename... Args>
void StaticMethod::invoke(Args&&... arguments) const noexcept
{
	//TODO Security check


}

/**
*	Invoke the method with the provided arguments if the return type and argument types match this method prototype
*/
template <typename ReturnType, typename... Args>
ReturnType StaticMethod::invoke(Args&&... arguments) const noexcept
{
	//TODO
}

template <typename... Args>
void StaticMethod::safeInvoke(Args&&... arguments) const noexcept
{
	//TODO
}

template <typename ReturnType, typename... Args>
ReturnType StaticMethod::safeInvoke(Args&&... arguments) const noexcept
{
	//TODO
}