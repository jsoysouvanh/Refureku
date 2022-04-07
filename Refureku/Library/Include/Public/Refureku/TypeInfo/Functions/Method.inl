/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

////////////////// MemberFunctionSafeCallWrapper

template <typename CallerType, typename ReturnType, typename... ArgTypes>
ReturnType Method::MemberFunctionSafeCallWrapper<CallerType, ReturnType(ArgTypes...)>::invoke(MemberFunction<std::remove_const_t<CallerType>, ReturnType(ArgTypes...)> const& function, CallerType& caller, ArgTypes&&... args)
{
	//Some hacky implementation for MSVC to handle the fact that
	//pointer to member functions can have different sizes based on the class inheritance
	//In release mode, eventhough the size doesn't match, the method call seems to work...
	//Might remove the RFK_DEBUG check if problems are encountered
#if (defined(_WIN32) || defined(_WIN64)) && RFK_DEBUG

	//Define all cases that generate different pointer to member function sizes
	class NoInheritanceClass {};	//No inheritance / Single inheritance -> x32: 4 / x64: 8
	class NoInheritanceClass2 {};
	class MultipleInheritanceClass : public NoInheritanceClass, public NoInheritanceClass2 {};	//Multiple inheritance -> x32: 8 / x64: 16
	class VirtualInheritanceClass : public virtual NoInheritanceClass {}; //Virtual inheritance -> x32: 16 / x64: 16

	switch (function.getOriginalFunctionSize())
	{
		case (sizeof(PointerToMemberMethod<NoInheritanceClass>)):
			return reinterpret_cast<MemberFunction<NoInheritanceClass, ReturnType(ArgTypes...)> const&>(function).operator()(reinterpret_cast<CopyConstness<CallerType, NoInheritanceClass>::Type&>(caller), std::forward<ArgTypes>(args)...);

		case (sizeof(PointerToMemberMethod<MultipleInheritanceClass>)):
			return reinterpret_cast<MemberFunction<MultipleInheritanceClass, ReturnType(ArgTypes...)> const&>(function).operator()(reinterpret_cast<CopyConstness<CallerType, MultipleInheritanceClass>::Type&>(caller), std::forward<ArgTypes>(args)...);

#if !defined(_WIN64) //_WIN32
		case (sizeof(PointerToMemberMethod<VirtualInheritanceClass>)):
			return reinterpret_cast<MemberFunction<VirtualInheritanceClass, ReturnType(ArgTypes...)> const&>(function).operator()(reinterpret_cast<CopyConstness<CallerType, VirtualInheritanceClass>::Type&>(caller), std::forward<ArgTypes>(args)...);
#endif

		default:
			assert(false);
	}
#else
	//No trick required, pointer to member function size do not vary with class inheritance on GCC / Clang
	return function.operator()(caller, std::forward<ArgTypes>(args)...);
#endif
}

////////////////// Method

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::internalInvoke(CallerType& caller, ArgTypes&&... args) const
{
	return MemberFunctionSafeCallWrapper<CallerType, ReturnType(ArgTypes...)>::invoke(
			*reinterpret_cast<MemberFunction<std::remove_const_t<CallerType>, ReturnType(ArgTypes...)>*>(getInternalFunction()),
			caller,
			std::forward<ArgTypes>(args)...
	);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes, typename>
ReturnType Method::invoke(CallerType& caller, ArgTypes&&... args) const
{
	return internalInvoke<ReturnType, CallerType, ArgTypes...>(adjustCallerAddress(caller), std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::invoke(CallerType const& caller, ArgTypes&&... args) const
{
	if (!isConst())
	{
		throwConstViolationException("Can't call a non-const member function on a const caller instance.");
	}

	return internalInvoke<ReturnType, CallerType const, ArgTypes...>(adjustCallerAddress(caller), std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes, typename>
ReturnType Method::checkedInvoke(CallerType& caller, ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();

	return invoke<ReturnType, CallerType, ArgTypes...>(checkedAdjustCallerAddress(caller), std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes>
ReturnType Method::checkedInvoke(CallerType const& caller, ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();

	return invoke<ReturnType, CallerType, ArgTypes...>(checkedAdjustCallerAddress(caller), std::forward<ArgTypes>(args)...);
}