/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
void Struct::__RFKaddToParents([[maybe_unused]] EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (rfk::isReflectedClass<T>)
	{
		directParents.emplace(rfk::Struct::Parent{ inheritanceAccess, &T::staticGetArchetype() });
	}
}

template <typename ReturnType, typename... ArgTypes>
Method const* Struct::getMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	auto range = methods.equal_range(Method(std::string(methodName)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->flags & minFlags) == minFlags && it->hasSamePrototype<ReturnType, ArgTypes...>())
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectParents)
	{
		Method const* result = nullptr;

		for (Struct::Parent const& parent : directParents)
		{
			result = parent.type->getMethod(methodName, minFlags, true);

			if (result != nullptr)
			{
				return result;
			}
		}
	}

	return nullptr;
}

template <typename ReturnType, typename... ArgTypes>
StaticMethod const* Struct::getStaticMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	auto range = staticMethods.equal_range(StaticMethod(std::string(methodName)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->flags & minFlags) == minFlags && it->hasSamePrototype<ReturnType, ArgTypes...>())
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectParents)
	{
		StaticMethod const* result = nullptr;

		for (Struct::Parent const& parent : directParents)
		{
			result = parent.type->getStaticMethod(methodName, minFlags, true);

			if (result != nullptr)
			{
				return result;
			}
		}
	}

	return nullptr;
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstanceFromCustomInstantiator(ArgTypes&&... args) const noexcept
{
	for (StaticMethod const* instantiator : customInstantiators)
	{
		if (instantiator->hasSameArguments<ArgTypes...>())
		{
			return static_cast<ReturnType*>(instantiator->invoke<void*, ArgTypes...>(std::forward<ArgTypes>(args)...));
		}
	}

	return nullptr;
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstance(ArgTypes&&... args) const noexcept
{
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>);

	if constexpr (sizeof...(args) == 0)
	{
		//No arguments, use default instantiator
		return (_defaultInstantiator != nullptr) ? static_cast<ReturnType*>((*_defaultInstantiator)()) : makeInstanceFromCustomInstantiator<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
	}
	else
	{
		return makeInstanceFromCustomInstantiator<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
	}
}

template <typename T>
void Struct::__RFKaddRequiredMethods() noexcept
{
	__RFKsetDefaultInstantiationMethod(&T::template __RFKinstantiate<T>);
}

template <typename ReturnType>
void Struct::__RFKaddCustomInstantiator(StaticMethod const* instantiator) noexcept
{
	static_assert(std::is_same_v<ReturnType, void*>, "A CustomInstantiator method must return void*");

	assert(instantiator != nullptr);

	//Make sure the instantiator is valid - i.e. its return type is a pointer type
	customInstantiators.emplace_back(instantiator);
}