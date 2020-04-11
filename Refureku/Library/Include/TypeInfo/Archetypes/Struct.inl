
template <typename T>
void Struct::__RFKaddToParents([[maybe_unused]] EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (rfk::isReflectedClass<T>)
	{
		directParents.emplace(rfk::Struct::Parent{ inheritanceAccess, &T::staticGetArchetype() });
	}
}