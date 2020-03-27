
template <typename T>
void Type::__RFKaddToParentsIfPossible(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (refureku::generated::implements_staticGetType<T, refureku::Type const&()>::value)
	{
		directParents.emplace_back(refureku::Type::Parent{ inheritanceAccess, T::staticGetType() });
	}
}

template <typename T>
void Type::__RFKaddRequiredMethods(std::string&& instantiatePrototype) noexcept
{
	static std::hash<std::string> stringHasher;

	__RFKaddInstantiationMethod<T>(	"__RFKinstantiate",
										stringHasher(name + "__RFKinstantiate" + instantiatePrototype),
										refureku::EAccessSpecifier::Private,
										&T::template __RFKinstantiate<T>);
}

template <typename ReturnType, typename... ArgTypes>
void Type::__RFKaddInstantiationMethod(std::string&& methodName, uint64 methodId, refureku::EAccessSpecifier accessSpecifier, ReturnType*(*function)(ArgTypes...)) noexcept
{
	//Insert at the right place in the vector (alphabetical order)
	staticMethods.insert(std::lower_bound(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)), [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; }),
						 StaticMethod(std::forward<std::string>(methodName), methodId, accessSpecifier, std::shared_ptr<refureku::NonMemberFunction<ReturnType*(ArgTypes...)>>(new refureku::NonMemberFunction<ReturnType*(ArgTypes...)>(function))));
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Type::makeInstance(ArgTypes&&... args) const noexcept
{
	//Get right instantiate according to ReturnType & ArgTypes
	StaticMethod const* instantiator = getStaticMethod("__RFKinstantiate");	// <-- TODO search with static types getStaticMethod<ReturnType(ArgTypes...)>("__RFKinstantiate");

	if (instantiator != nullptr)
		return instantiator->invoke<ReturnType*>(std::forward<ArgTypes>(args)...);
	else
		return nullptr;
}