
template <typename ReturnType, typename... ArgTypes>
ReturnType* Archetype::makeInstance(ArgTypes&&... args) const noexcept
{
	if constexpr (sizeof...(args) == 0)
	{
		//No arguments, use default instantiator
		return reinterpret_cast<ReturnType*>((*_defaultInstantiator)());
	}
	else
	{
		//	//Get right instantiate according to ReturnType & ArgTypes
		//	StaticMethod const* instantiator = getStaticMethod("__RFKinstantiate");	// <-- TODO search with static types getStaticMethod<ReturnType(ArgTypes...)>("__RFKinstantiate");

		//	if (instantiator != nullptr)
		//		return instantiator->invoke<ReturnType*>(std::forward<ArgTypes>(args)...);
		//	else
		return nullptr;
	}
}

template <typename T>
void Archetype::__RFKaddRequiredMethods() noexcept
{
	if constexpr (std::is_class_v<T>)
	{
		_defaultInstantiator = &T::template __RFKinstantiate<T>;
	}
	else
	{
		//Enum, fundamental types
		_defaultInstantiator = []() -> void* { return new T(); };
	}
}