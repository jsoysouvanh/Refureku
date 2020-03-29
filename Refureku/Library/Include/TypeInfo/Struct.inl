
template <typename T>
void Struct::__RFKaddToParents(EAccessSpecifier inheritanceAccess) noexcept
{
	if constexpr (rfk::generated::implements_staticGetArchetype<T, rfk::Struct const&()>::value)
	{
		directParents.emplace_back(rfk::Struct::Parent{ inheritanceAccess, T::staticGetArchetype() });
	}
}

template <typename T>
void Struct::__RFKaddRequiredMethods(std::string&& instantiatePrototype) noexcept
{
	static std::hash<std::string> stringHasher;

	//TODO: Don't add Default instantiate method, neither should it be generated for each reflected class
	//Make the default implementation in base reflection class and keep a reference to all instantiation classes in a separated array
	__RFKaddInstantiationMethod<T>(	"__RFKinstantiate",
										stringHasher(name + "__RFKinstantiate" + instantiatePrototype),
										rfk::EAccessSpecifier::Private,
										&T::template __RFKinstantiate<T>);
}

template <typename ReturnType, typename... ArgTypes>
void Struct::__RFKaddInstantiationMethod(std::string&& methodName, uint64 methodId, rfk::EAccessSpecifier accessSpecifier, ReturnType*(*function)(ArgTypes...)) noexcept
{
	//TODO: Move this method in another specific array

	//Insert in the sorted order vector (alphabetical order)
	//staticMethods.insert(std::lower_bound(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)), [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; }),
	//					 StaticMethod(std::forward<std::string>(methodName), methodId, accessSpecifier, std::shared_ptr<rfk::NonMemberFunction<ReturnType*(ArgTypes...)>>(new rfk::NonMemberFunction<ReturnType*(ArgTypes...)>(function))));
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstance(ArgTypes&&... args) const noexcept
{
	//Get right instantiate according to ReturnType & ArgTypes
	StaticMethod const* instantiator = getStaticMethod("__RFKinstantiate");	// <-- TODO search with static types getStaticMethod<ReturnType(ArgTypes...)>("__RFKinstantiate");

	if (instantiator != nullptr)
		return instantiator->invoke<ReturnType*>(std::forward<ArgTypes>(args)...);
	else
		return nullptr;
}