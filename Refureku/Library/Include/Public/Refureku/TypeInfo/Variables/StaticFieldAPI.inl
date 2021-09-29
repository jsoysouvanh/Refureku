/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ValueType>
ValueType StaticFieldAPI::get() const
{
	return VariableBaseAPI::get<ValueType>(getPtr());
}

template <typename ValueType>
void StaticFieldAPI::set(ValueType&& data) const
{
	VariableBaseAPI::set(getPtr(), std::forward<ValueType>(data));
}