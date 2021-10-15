/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstance(ArgTypes&&... args) const
{
	static_assert(!std::is_void_v<ReturnType>, "Returning void* is forbidden since deleting a void* pointer is undefined.");
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>);

	if constexpr (sizeof...(args) == 0u)
	{
		//No arguments, use default instantiator
		return reinterpret_cast<ReturnType*>(makeInstanceFromDefaultInstantiator());
	}
	else
	{
		StaticMethod const* instantiator;

		for (std::size_t i = 0u; i < getInstantiatorsCount(); i++)
		{
			instantiator = getInstantiatorAt(i);

			if (instantiator->hasSameParameters<ArgTypes...>())
			{
				//Custom instantiators are guaranteed to return void*
				return reinterpret_cast<ReturnType*>(instantiator->invoke<void*>(std::forward<ArgTypes>(args)...));
			}
		}

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
																	internal::MethodHelper<MethodSignature>::hasSamePrototype(methodBase);
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
																internal::MethodHelper<StaticMethodSignature>::hasSamePrototype(methodBase);
													}, &data, shouldInspectInherited) : nullptr;
}

template <typename T>
void* internal::defaultInstantiator()
{
	if constexpr (std::is_default_constructible_v<T>)
	{
		return new T();
	}
	else
	{
		return nullptr;
	}
}