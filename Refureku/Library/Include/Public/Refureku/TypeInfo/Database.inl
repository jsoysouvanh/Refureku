/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename FunctionSignature>
Function const* Database::getFileLevelFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	struct Data
	{
		char const*		name;
		EFunctionFlags	flags;
	} data{ name, flags };

	return (name != nullptr) ? getFileLevelFunctionByPredicate([](Function const& func, void* data)
													{
														Data const&	userData = *reinterpret_cast<Data*>(data);

														return (userData.flags & func.getFlags()) == userData.flags &&
																func.hasSameName(userData.name) &&
																internal::FunctionHelper<FunctionSignature>::hasSameSignature(func);
													}, &data) : nullptr;
}