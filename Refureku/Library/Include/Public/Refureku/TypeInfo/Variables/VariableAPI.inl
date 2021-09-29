/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ValueType>
ValueType VariableAPI::get() const
{
	return VariableBaseAPI::get<ValueType>(getPtr());
}

template <typename ValueType>
void VariableAPI::set(ValueType&& value) const
{
	VariableBaseAPI::set(getPtr(), std::forward<ValueType>(value));
}