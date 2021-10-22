/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
rfk::SharedPtr<ReturnType> Struct::makeSharedInstance(ArgTypes&&... args) const
{
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>);

	StaticMethod const* instantiator;

	//TODO: Order instantiators by arg counts, and abort the loop early if the number of args is greater than sizeof...(ArgTypes)
	//TODO: Should add a foreachInstantiator to avoid multiple getInstantiatorAt calls
	for (std::size_t i = 0u; i < getInstantiatorsCount(); i++)
	{
		instantiator = getInstantiatorAt(i);

		if (instantiator->hasSameParameters<ArgTypes...>())
		{
			//Custom instantiators are guaranteed to return void*
			return instantiator->invoke<rfk::SharedPtr<ReturnType>>(std::forward<ArgTypes>(args)...);
		}
	}

	return nullptr;
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