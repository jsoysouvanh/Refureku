
template <typename T>
void Class::__RFKaddToParents(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (refureku::generated::implements_staticGetArchetype<T, refureku::Class const&()>::value)
	{
		directParents.emplace_back(refureku::Struct::Parent{ inheritanceAccess, &T::staticGetArchetype() });
	}
}