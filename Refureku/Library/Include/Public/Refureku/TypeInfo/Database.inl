/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename FunctionSignature>
Function const* Database::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	for (Function const* function : getFunctionsByName(name, flags))
	{
		if (internal::FunctionHelper<FunctionSignature>::hasSamePrototype(*function))
		{
			return function;
		}
	}

	return nullptr;
}