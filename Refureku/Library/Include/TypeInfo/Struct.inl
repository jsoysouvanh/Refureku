
template <typename T>
void Struct::__RFKaddToParents(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (rfk::generated::implements_staticGetArchetype<T, rfk::Struct const&()>::value)
	{
		directParents.emplace(rfk::Struct::Parent{ inheritanceAccess, T::staticGetArchetype() });
	}
}