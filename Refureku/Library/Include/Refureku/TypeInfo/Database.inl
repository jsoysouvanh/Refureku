/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename FunctionSignature>
Function const* Database::getFunction(std::string functionName, EFunctionFlags flags) noexcept
{
	Entity searchedFunction(std::move(functionName), 0u);

	//Use an Entity instead of a Function to avoid memory / allocation overhead
	auto range = _fileLevelFunctionsByName.equal_range(static_cast<Function const*>(&searchedFunction));

	for (auto it = range.first; it != range.second; it++)
	{
		if (((*it)->flags & flags) == flags && internal::FunctionHelper<FunctionSignature>::hasSamePrototype(**it))
		{
			//We found a method which has minFlags and matches the signature
			return *it;
		}
	}

	return nullptr;
}