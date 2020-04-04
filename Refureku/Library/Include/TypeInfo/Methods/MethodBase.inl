
template <typename... ArgTypes>
void MethodBase::checkArgumentsStrict(ArgTypes&&... args) const
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
		checkArgumentsStrict<0>(std::forward<ArgTypes>(args)...);
	}
}

template <size_t Rank, typename FirstArgType, typename... OtherArgTypes>
void MethodBase::checkArgumentsStrict(FirstArgType&& a, OtherArgTypes&&... args) const
{
	checkArgumentsStrict<Rank, FirstArgType>(std::forward<FirstArgType>(a));
	checkArgumentsStrict<Rank + 1, OtherArgTypes...>(std::forward<OtherArgTypes>(args)...);
}

template <size_t Rank, typename LastArgType>
void MethodBase::checkArgumentsStrict(LastArgType&& a) const
{
	Type providedType = Type::getType<LastArgType>();

	if (providedType != parameters[Rank].type)
	{
		throw MethodError("Tried to call method " + name + " but argument " + std::to_string(Rank) + " (" + parameters[Rank].name + ") type doesn't match.\n" +
						  "Provided: \n" + providedType.toString() + "\nExpected: \n" + parameters[Rank].type.toString());
	}
}

template <typename... ArgTypes>
void MethodBase::checkArgumentsLax(ArgTypes&&... args) const
{

}

template <typename ReturnType>
void MethodBase::checkReturnTypeStrict() const
{
	Type providedType = Type::getType<ReturnType>();

	if (providedType != returnType)
	{
		throw MethodError("The specified return type is incorrect.\nProvided: \n" + providedType.toString() + "\nExpected: \n" + returnType.toString());
	}
}

template <typename ReturnType>
void MethodBase::checkReturnTypeLax() const
{

}