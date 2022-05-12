/**
*	Copyright (c) 2021-2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

////////////////// MemberFunctionSafeCallWrapper

template <typename ReturnType, typename... ArgTypes>
template <typename T, typename>
ReturnType Method::MemberFunctionSafeCallWrapper<ReturnType(ArgTypes...)>::invoke(ICallable const& method, T* caller, ArgTypes&&... args)
{
	//Some hacky implementation for MSVC to handle the fact that
	//pointer to member functions can have different sizes based on the class inheritance
	class NoInheritanceClass {};

#if (defined(_WIN32) || defined(_WIN64))

	//Define all cases that generate different pointer to member function sizes
	//class NoInheritanceClass {};	//No inheritance / Single inheritance -> x32: 4 / x64: 8
	class NoInheritanceClass2 {};
	class MultipleInheritanceClass : public NoInheritanceClass, public NoInheritanceClass2 {};	//Multiple inheritance -> x32: 8 / x64: 16
	class VirtualInheritanceClass : public virtual NoInheritanceClass {}; //Virtual inheritance -> x32: 16 / x64: 16

	switch (reinterpret_cast<MemberFunction<NoInheritanceClass, ReturnType(ArgTypes...)> const&>(method).getOriginalFunctionSize())
	{
		case (sizeof(PointerToMemberMethod<NoInheritanceClass>)):
			return reinterpret_cast<MemberFunction<NoInheritanceClass, ReturnType(ArgTypes...)> const&>(method).operator()(*reinterpret_cast<typename CopyConstness<T, NoInheritanceClass>::Type*>(caller), std::forward<ArgTypes>(args)...);

		case (sizeof(PointerToMemberMethod<MultipleInheritanceClass>)):
			return reinterpret_cast<MemberFunction<MultipleInheritanceClass, ReturnType(ArgTypes...)> const&>(method).operator()(*reinterpret_cast<typename CopyConstness<T, MultipleInheritanceClass>::Type*>(caller), std::forward<ArgTypes>(args)...);

#if !defined(_WIN64) //_WIN32
		case (sizeof(PointerToMemberMethod<VirtualInheritanceClass>)):
			return reinterpret_cast<MemberFunction<VirtualInheritanceClass, ReturnType(ArgTypes...)> const&>(method).operator()(*reinterpret_cast<typename CopyConstness<T, VirtualInheritanceClass>::Type*>(caller), std::forward<ArgTypes>(args)...);
#endif

		default:
			assert(false);

			//Fake a return to avoid warnings
			//Should never reach this point anyway
			return reinterpret_cast<ReturnType (*)()>(0)();
	}
#else
	//No trick required, pointer to member function size does not vary with class inheritance on GCC / Clang
	//Cast to a random dummy class just to fake a class member (because we can't have a MemberFunction<void, ...>).
	return reinterpret_cast<MemberFunction<NoInheritanceClass, ReturnType(ArgTypes...)> const&>(method).operator()(*reinterpret_cast<typename CopyConstness<T, NoInheritanceClass>::Type*>(caller), std::forward<ArgTypes>(args)...);
#endif
}

////////////////// Method

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::internalInvoke(void* caller, ArgTypes&&... args) const
{
	return MemberFunctionSafeCallWrapper<ReturnType(ArgTypes...)>::invoke(*getInternalFunction(), caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::internalInvoke(void const* caller, ArgTypes&&... args) const
{
	return MemberFunctionSafeCallWrapper<ReturnType(ArgTypes...)>::invoke(*getInternalFunction(), caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes, typename>
ReturnType Method::invoke(CallerType& caller, ArgTypes&&... args) const
{
	return invokeUnsafe<ReturnType, ArgTypes...>(adjustCallerPointerAddress(&caller),
												 std::forward<ArgTypes>(args)...
												 );
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::invokeUnsafe(void* caller, ArgTypes&&... args) const
{
	return internalInvoke<ReturnType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::invokeUnsafe(void const* caller, ArgTypes&&... args) const
{
	if (!isConst())
	{
		throwConstViolationException();
	}

	return internalInvoke<ReturnType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename CallerType, typename... ArgTypes, typename>
ReturnType Method::checkedInvoke(CallerType& caller, ArgTypes&&... args) const
{
	return checkedInvokeUnsafe<ReturnType, ArgTypes...>(adjustCallerPointerAddress(&caller),
														std::forward<ArgTypes>(args)...
														);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::checkedInvokeUnsafe(void* caller, ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();

	return internalInvoke<ReturnType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType Method::checkedInvokeUnsafe(void const* caller, ArgTypes&&... args) const
{
	if (!isConst())
	{
		throwConstViolationException();
	}

	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();

	return internalInvoke<ReturnType, ArgTypes...>(caller, std::forward<ArgTypes>(args)...);
}

template <typename CallerType>
CallerType* Method::adjustCallerPointerAddress(CallerType* caller) const
{
	//Non-virtual methods can be called with non-adjusted instances (doesn't use virtual table)
	if (!isVirtual())
	{
		return caller;
	}

	CallerType* adjustedCallerPointer = rfk::dynamicCast<CallerType>(caller, CallerType::staticGetArchetype(), caller->getArchetype(), *static_cast<rfk::Struct const*>(getOuterEntity()));

	if (adjustedCallerPointer != nullptr)
	{
		return adjustedCallerPointer;
	}
	else
	{
		throw InvalidArchetype("Failed to adjust the caller pointer since it has no relationship with the method's outer struct.");
	}
}