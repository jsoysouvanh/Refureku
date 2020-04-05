
template <typename T>
void Struct::__RFKaddToParents(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (rfk::isReflectedClass<T>)
	{
		directParents.emplace(rfk::Struct::Parent{ inheritanceAccess, &T::staticGetArchetype() });
	}
}