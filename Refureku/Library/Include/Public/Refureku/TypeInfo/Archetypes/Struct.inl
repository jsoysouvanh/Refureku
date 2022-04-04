/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
rfk::SharedPtr<ReturnType> Struct::makeSharedInstance(ArgTypes&&... args) const
{
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>, "The return type of makeSharedInstance should not be a pointer or a reference.");
	
	StaticMethod const* result;

	if (!foreachSharedInstantiator(sizeof...(args), [](StaticMethod const& instantiator, void* data)
		{
			//Find a shared instantiator with the same parameters
			if (instantiator.hasSameParameters<ArgTypes...>())
			{
				*reinterpret_cast<StaticMethod const**>(data) = &instantiator;
				return false;
			}

			return true;
		}, &result))
	{
		assert(result != nullptr);

		return result->invoke<rfk::SharedPtr<ReturnType>>(std::forward<ArgTypes>(args)...);
	}
	else
	{
		//Try with unique instantiators
		rfk::UniquePtr<ReturnType> uniqueInstance = makeUniqueInstance<ReturnType>(std::forward<ArgTypes>(args)...);

		return (uniqueInstance.get() != nullptr) ?
				rfk::SharedPtr<ReturnType>(std::move(uniqueInstance)) :
				nullptr;
	}
}

template <typename ReturnType, typename... ArgTypes>
rfk::UniquePtr<ReturnType> Struct::makeUniqueInstance(ArgTypes&&... args) const
{
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>, "The return type of makeUniqueInstance should not be a pointer or a reference.");

	StaticMethod const* result;

	if (!foreachUniqueInstantiator(sizeof...(args), [](StaticMethod const& instantiator, void* data)
		{
			//Find an instantiator with the same parameters
			if (instantiator.hasSameParameters<ArgTypes...>())
			{
				*reinterpret_cast<StaticMethod const**>(data) = &instantiator;
				return false;
			}

			return true;
		}, &result))
	{
		assert(result != nullptr);

		return result->invoke<rfk::UniquePtr<ReturnType>>(std::forward<ArgTypes>(args)...);
	}
	else
	{
		return nullptr;
	}
}

template <typename MethodSignature>
Method const* Struct::getMethodByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	struct Data
	{
		char const*		name;
		EMethodFlags	flags;
	} data{ name, minFlags };

	return (name != nullptr) ? getMethodByPredicate([](Method const& method, void* data)
													  {
														  MethodBase const&	methodBase = *reinterpret_cast<MethodBase const*>(&method);
														  Data const&		userData = *reinterpret_cast<Data*>(data);

														  return (userData.flags & methodBase.getFlags()) == userData.flags &&
																	methodBase.hasSameName(userData.name) &&
																	internal::MethodHelper<MethodSignature>::hasSameSignature(methodBase);
													  }, &data, shouldInspectInherited) : nullptr;
}

template <typename StaticMethodSignature>
StaticMethod const* Struct::getStaticMethodByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	struct Data
	{
		char const*		name;
		EMethodFlags	flags;
	} data{ name, minFlags };

	return (name != nullptr) ? getStaticMethodByPredicate([](StaticMethod const& method, void* data)
													{
														MethodBase const&	methodBase = *reinterpret_cast<MethodBase const*>(&method);
														Data const&			userData = *reinterpret_cast<Data*>(data);

														return (userData.flags & methodBase.getFlags()) == userData.flags &&
																methodBase.hasSameName(userData.name) &&
																internal::MethodHelper<StaticMethodSignature>::hasSameSignature(methodBase);
													}, &data, shouldInspectInherited) : nullptr;
}