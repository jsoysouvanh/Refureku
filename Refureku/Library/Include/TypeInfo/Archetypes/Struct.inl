
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