
template <typename T>
void Class::__RFKaddToParentsIfPossible(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (refureku::generated::implements_staticGetArchetype<T, refureku::Class const&()>::value)
	{
		directParents.emplace_back(refureku::Struct::Parent{ inheritanceAccess, T::staticGetArchetype() });
	}
}