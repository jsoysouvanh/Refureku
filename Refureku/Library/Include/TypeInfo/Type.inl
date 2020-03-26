
template <typename T>
void Type::addToParentsIfPossible(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (refureku::generated::implements_staticGetType<T, refureku::Type const&()>::value)
	{
		directParents.emplace_back(refureku::Type::Parent{ inheritanceAccess, T::staticGetType() });
	}
}