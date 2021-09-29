/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType>
bool FunctionBaseAPI::hasSameReturnType() const noexcept
{
	return rfk::getTypeAPI<ReturnType>() == getReturnType();
}

template <typename... ArgTypes>
bool FunctionBaseAPI::hasSameParametersCount() const noexcept
{
	return sizeof...(ArgTypes) == getParametersCount();
}

template <typename... ArgTypes>
bool FunctionBaseAPI::hasSameParameterTypes() const noexcept
{
	return hasSameParameterTypes<0u, ArgTypes...>();
}

template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
bool FunctionBaseAPI::hasSameParameterTypes() const noexcept
{
	return hasSameParameterTypes<Rank, FirstArgType>() && hasSameParameterTypes<Rank + 1, SecondArgType, OtherArgTypes...>();
}

template <size_t Rank, typename LastArgType>
bool FunctionBaseAPI::hasSameParameterTypes() const noexcept
{
	return getParameterAt(Rank).getType() == rfk::getTypeAPI<LastArgType>();
}

template <typename... ArgTypes>
bool FunctionBaseAPI::hasSameParameters() const noexcept
{
	if constexpr (sizeof...(ArgTypes) == 0u)
	{
		return getParametersCount() == 0u;
	}
	else
	{
		return hasSameParametersCount<ArgTypes...>() && hasSameParameterTypes<ArgTypes...>();
	}
}

template <typename ReturnType, typename... ArgTypes>
bool FunctionBaseAPI::hasSamePrototype() const noexcept
{
	if constexpr (sizeof...(ArgTypes) == 0u)
	{
		//Check only return type if there are no arguments
		return getParametersCount() == 0u && hasSameReturnType<ReturnType>();
	}
	else
	{
		return hasSameParametersCount<ArgTypes...>() && hasSameReturnType<ReturnType>() && hasSameParameterTypes<ArgTypes...>();
	}
}

template <typename... ArgTypes>
void FunctionBaseAPI::checkParametersCount() const
{
	if (!hasSameParametersCount<ArgTypes...>())
	{
		throw ArgCountMismatch("Provided number of parameters doesn't match");
	}
}

template <typename... ArgTypes>
void FunctionBaseAPI::checkParameters() const
{
	checkParametersCount();

	if (!hasSameParameters<ArgTypes...>())
	{
		throw ArgCountMismatch("Provided parameters doesn't match");
	}
}

template <typename ReturnType>
void FunctionBaseAPI::checkReturnType() const
{
	if (!hasSameReturnType<ReturnType>())
	{
		throw ReturnTypeMismatch("Provided return type doesn't match");
	}
}