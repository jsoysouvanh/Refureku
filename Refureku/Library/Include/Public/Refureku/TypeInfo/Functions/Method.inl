/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::internalInvoke(CallerType& caller, ArgTypes&&... args) const
{
	return reinterpret_cast<MemberFunction<CallerType, ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::internalInvoke(CallerType const& caller, ArgTypes&&... args) const
{
	return reinterpret_cast<MemberFunction<CallerType, ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::invoke(CallerType& caller, ArgTypes&&... args) const
{
	return internalInvoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::invoke(CallerType const& caller, ArgTypes&&... args) const
{
	if (!isConst())
	{
		throwConstViolationException("Can't call a non-const member function on a const caller instance.");
	}

	return internalInvoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::checkedInvoke(CallerType& caller, ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();
	//TODO: Add caller type check?

	return invoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::checkedInvoke(CallerType const& caller, ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();
	//TODO: Add caller type check?

	return invoke<ReturnType, CallerType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}