
template <typename... ArgTypes>
void MethodBase::checkArguments(ArgTypes&&... args) const
{
	size_t correctParamCount = parameters.size();

	//Check the number of provided params is correct
	if (sizeof...(ArgTypes) != correctParamCount)
	{
		throw MethodError("Tried to call method " + name + " with " + std::to_string(sizeof...(args)) + " parameters but " + std::to_string(correctParamCount) + " were expected.");
	}

	//Check that each provided param type is strictly identical to what we expect
	if constexpr (sizeof...(ArgTypes) != 0u)
	{
		checkArguments<0>(std::forward<ArgTypes>(args)...);
	}
}

template <size_t Rank, typename FirstArgType, typename... OtherArgTypes>
void MethodBase::checkArguments(FirstArgType&& a, OtherArgTypes&&... args) const
{
	checkArguments<Rank, FirstArgType>(std::forward<FirstArgType>(a));
	checkArguments<Rank + 1, OtherArgTypes...>(std::forward<OtherArgTypes>(args)...);
}

template <size_t Rank, typename LastArgType>
void MethodBase::checkArguments(LastArgType&& a) const
{
	Type providedType = Type::getType<LastArgType>();

	if (!parameters[Rank].type.match(providedType))
	{
		throw MethodError("Tried to call method " + name + " but argument " + std::to_string(Rank) + " (" + parameters[Rank].name + ") type doesn't match.\n" +
						  "Provided: \n" + providedType.toString() + "\nExpected: \n" + parameters[Rank].type.toString());
	}
}

template <typename ReturnType>
void MethodBase::checkReturnType() const
{
	Type providedType = Type::getType<ReturnType>();

	if (!returnType.match(providedType))
	{
		throw MethodError("The specified return type is incorrect.\nProvided: \n" + providedType.toString() + "\nExpected: \n" + returnType.toString());
	}
}