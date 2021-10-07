/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ValueType>
ValueType Variable::get() const
{
	return VariableBase::get<ValueType>(getPtr());
}

template <typename ValueType>
void Variable::set(ValueType&& value) const
{
	VariableBase::set(getPtr(), std::forward<ValueType>(value));
}