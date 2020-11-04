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

template <typename MethodSignature>
Method const* Struct::getMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	static_assert(std::is_function_v<MethodSignature>, "Struct::getMethod<> must be called with a function signature as template argument.");

	//Use an Entity instead of a Method to avoid memory / allocation overhead
	auto range = methods.equal_range(static_cast<Method&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->flags & minFlags) == minFlags && internal::MethodHelper<MethodSignature>::hasSamePrototype(*it))
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

template <typename MethodSignature>
StaticMethod const* Struct::getStaticMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	static_assert(std::is_function_v<MethodSignature>, "Struct::getStaticMethod<> must be called with a function signature as template argument.");

	//Use an Entity instead of a StaticMethod to avoid memory / allocation overhead
	auto range = staticMethods.equal_range(static_cast<StaticMethod&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->flags & minFlags) == minFlags && internal::MethodHelper<MethodSignature>::hasSamePrototype(*it))
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
ReturnType* Struct::makeInstanceFromCustomInstantiator(ArgTypes&&... args) const
{
	for (StaticMethod const* instantiator : customInstantiators)
	{
		if (instantiator->hasSameArguments<ArgTypes...>())
		{
			return static_cast<ReturnType*>(instantiator->rInvoke<void*>(std::forward<ArgTypes>(args)...));
		}
	}

	return nullptr;
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstance(ArgTypes&&... args) const
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
	assert(instantiator != nullptr);

	//Make sure the instantiator is valid - i.e. its return type is a pointer type
	customInstantiators.emplace_back(instantiator);
}