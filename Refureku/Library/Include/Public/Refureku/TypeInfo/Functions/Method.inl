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

			//Fake a return to avoid warnings
			//Should never reach this point anyway
			return reinterpret_cast<ReturnType (*)()>(nullptr)();
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

template <typename CallerType>
CallerType& Method::adjustCallerAddress(CallerType& caller) const noexcept
{
	if constexpr (internal::implements_getArchetype<CallerType, Struct const& ()>::value)
	{
		return adjustCallerAddress(caller, caller.getArchetype());
	}
	else
	{
		//Can't retrieve the dynamic archetype through a virtual getArchetype call, so use the caller static archetype.
		// /!\ If a memory offset exists between the caller static and dynamic archetypes, the returned result is INCORRECT /!\ 
		return adjustCallerAddress(caller, *static_cast<rfk::Struct const*>(rfk::getArchetype<CallerType>()));
	}
}

template <typename CallerType>
CallerType& Method::adjustCallerAddress(CallerType& caller, Struct const& callerDynamicArchetype) const noexcept
{
	//No adjustment required if the method is not virtual
	//The adjustment is required for virtual methods to point to the correct vtable
	if (isVirtual())
	{
		rfk::Struct const* callerStaticArchetype = static_cast<rfk::Struct const*>(rfk::getArchetype<CallerType>());

		if (callerStaticArchetype != nullptr)
		{
			CallerType* adjustedCallerPointer = rfk::dynamicCast<CallerType>(&caller,
																			 *callerStaticArchetype,
																			 callerDynamicArchetype,
																			 *static_cast<rfk::Struct const*>(getOuterEntity())
																			);

			if (adjustedCallerPointer != nullptr)
			{
				return *adjustedCallerPointer;
			}
			else
			{
				//adjustCallerAddress doesn't fail if the dynamicCast fails, and the original caller is return as provided
				//The invoke call using this caller is UB.
			}
		}
	}

	return caller;
}

template <typename CallerType>
CallerType& Method::checkedAdjustCallerAddress(CallerType& caller) const
{
	static_assert(internal::implements_getArchetype<CallerType, Struct const& ()>::value,
				  "[Refureku] To perform all the safety checks, the caller must implement the getArchetype() method inherited from rfk::Object.");

	return adjustCallerAddress(caller, caller.getArchetype());
}

template <typename CallerType>
CallerType& Method::checkedAdjustCallerAddress(CallerType& caller, Struct const& callerDynamicArchetype) const
{
	//No adjustment required if the method is not virtual
	//The adjustment is required for virtual methods to point to the correct vtable
	if (isVirtual())
	{
		rfk::Struct const* callerStaticArchetype = static_cast<rfk::Struct const*>(rfk::getArchetype<CallerType>());

		if (callerStaticArchetype != nullptr)
		{
			CallerType* adjustedCallerPointer = rfk::dynamicCast<CallerType>(&caller,
																			 *callerStaticArchetype,
																			 callerDynamicArchetype,
																			 *static_cast<rfk::Struct const*>(getOuterEntity())
																			);

			if (adjustedCallerPointer != nullptr)
			{
				return *adjustedCallerPointer;
			}
			else
			{
				//At this point, the cast can only fail if caller is not in the same inheritance hierarchy as the method's owner struct
				throwInvalidCallerException();
			}
		}
		else
		{
			//Throw an exception if the caller class is not reflected
			throwNotReflectedClassException();
		}
	}

	return caller;
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
		throwConstViolationException();
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