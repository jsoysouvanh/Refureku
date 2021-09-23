/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
ReturnType Function::internalInvoke(ArgTypes&&... arguments) const noexcept
{
	return reinterpret_cast<NonMemberFunction<ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Function::invoke(ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	#if REFUREKU_DEBUG

	checkArgumentsCount<ArgTypes...>();

	#endif

	internalInvoke<void, ArgTypes...>(std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Function::rInvoke(ArgTypes&&... arguments) const noexcept(REFUREKU_RELEASE)
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

	#if REFUREKU_DEBUG

	checkArgumentsCount<ArgTypes...>();

	#endif

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<ArgTypes>(arguments)...);
}

template <typename... ArgTypes>
void Function::checkedInvoke(ArgTypes&&... arguments) const
{
	checkArguments<ArgTypes...>();

	internalInvoke<void, ArgTypes...>(std::forward<ArgTypes>(arguments)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Function::checkedRInvoke(ArgTypes&&... arguments) const
{
	static_assert(!std::is_void_v<ReturnType>, "ReturnType can't be void.");

	checkReturnType<ReturnType>();
	checkArguments<ArgTypes...>();

	return internalInvoke<ReturnType, ArgTypes...>(std::forward<ArgTypes>(arguments)...);
}

inline EFunctionFlags Function::getFlags() const noexcept
{
	return _flags;
}

inline bool Function::isInline() const noexcept
{
	return (getFlags() & EFunctionFlags::Inline) != EFunctionFlags::Default;
}

inline bool Function::isStatic() const noexcept
{
	return (getFlags() & EFunctionFlags::Static) != EFunctionFlags::Default;
}