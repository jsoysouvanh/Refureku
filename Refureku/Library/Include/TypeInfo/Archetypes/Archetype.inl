
template <typename ReturnType, typename... ArgTypes>
ReturnType* Archetype::makeInstance([[maybe_unused]] ArgTypes&&... args) const noexcept
{
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>);

	if constexpr (sizeof...(args) == 0)
	{
		//No arguments, use default instantiator
		return (_defaultInstantiator != nullptr) ? reinterpret_cast<ReturnType*>((*_defaultInstantiator)()) : nullptr;
	}
	else
	{
		for (StaticMethod const* instantiator : customInstantiators)
		{
			if (instantiator->hasSameArguments<ArgTypes...>())
			{
				return instantiator->invoke<ReturnType*, ArgTypes...>(std::forward<ArgTypes>(args)...);
			}
		}

		return nullptr;
	}
}

template <typename T>
void Archetype::__RFKaddRequiredMethods() noexcept
{
	if constexpr (std::is_class_v<T>)
	{
		__RFKsetDefaultInstantiationMethod(&T::template __RFKinstantiate<T>);
	}
}