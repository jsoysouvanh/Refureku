/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename... ArgTypes>
void FunctionBase::checkArgumentsCount() const
{
	std::size_t correctParamCount = getParameterCount();

	//Check the number of provided params is correct
	if (sizeof...(ArgTypes) != correctParamCount)
	{
		throw ArgCountMismatch("Tried to call method " + getName() + " with " + std::to_string(sizeof...(ArgTypes)) + " arguments but " + std::to_string(correctParamCount) + " were expected.");
	}
}

template <typename... ArgTypes>
void FunctionBase::checkArguments() const
{
	//Check that there is the right amount of parameters
	checkArgumentsCount<ArgTypes...>();

	//Check that each provided argument type is strictly identical to what we expect
	if constexpr (sizeof...(ArgTypes) != 0u)
	{
		checkArguments<0u, ArgTypes...>();
	}
}

template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
void FunctionBase::checkArguments() const
{
	checkArguments<Rank, FirstArgType>();
	checkArguments<Rank + 1, SecondArgType, OtherArgTypes...>();
}

template <size_t Rank, typename LastArgType>
void FunctionBase::checkArguments() const
{
	Type providedType = Type::getType<LastArgType>();

	if (!getParameter(Rank).getType().match(providedType))
	{
		throw ArgTypeMismatch("Tried to call method " + getName() + " but argument " + std::to_string(Rank) + " (" + getParameter(Rank).getName() + ") type doesn't match.\n" +
							  "Provided: \n" + providedType.toString() + "\nExpected: \n" + getParameter(Rank).getType().toString());
	}
}

template <typename ReturnType>
void FunctionBase::checkReturnType() const
{
	Type providedType = Type::getType<ReturnType>();

	if (!getReturnType().match(providedType))
	{
		throw ReturnTypeMismatch("The specified return type is incorrect.\nProvided: \n" + providedType.toString() + "\nExpected: \n" + getReturnType().toString());
	}
}

template <typename... ArgTypes>
bool FunctionBase::hasSameArgumentsCount() const noexcept
{
	return sizeof...(ArgTypes) == getParameterCount();
}

template <typename ReturnType>
bool FunctionBase::hasSameReturnType() const noexcept
{
	return Type::getType<ReturnType>() == getReturnType();
}

template <typename... ArgTypes>
bool FunctionBase::hasSameArgumentTypes() const noexcept
{
	return hasSameArgumentTypes<0u, ArgTypes...>();
}

template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
bool FunctionBase::hasSameArgumentTypes() const noexcept
{
	return hasSameArgumentTypes<Rank, FirstArgType>() && hasSameArgumentTypes<Rank + 1, SecondArgType, OtherArgTypes...>();
}

template <size_t Rank, typename LastArgType>
bool FunctionBase::hasSameArgumentTypes() const noexcept
{
	return getParameter(Rank).getType() == Type::getType<LastArgType>();
}

template <typename ReturnType, typename... ArgTypes>
bool FunctionBase::hasSamePrototype() const noexcept
{
	if constexpr (sizeof...(ArgTypes) == 0u)
	{
		//Check only return type if there are no arguments
		return getParameterCount() == 0u && hasSameReturnType<ReturnType>();
	}
	else
	{
		return hasSameArgumentsCount<ArgTypes...>() && hasSameReturnType<ReturnType>() && hasSameArgumentTypes<ArgTypes...>();
	}
}

template <typename... ArgTypes>
bool FunctionBase::hasSameArguments() const noexcept
{
	if constexpr (sizeof...(ArgTypes) == 0u)
	{
		return getParameterCount() == 0u;
	}
	else
	{
		return hasSameArgumentsCount<ArgTypes...>() && hasSameArgumentTypes<ArgTypes...>();
	}
}

inline Type const& FunctionBase::getReturnType() const noexcept
{
	return _returnType;
}