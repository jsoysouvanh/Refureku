/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ValueType>
ValueType StaticField::get() const
{
	if constexpr (VariableBase::is_value_v<ValueType> || std::is_const_v<std::remove_reference_t<ValueType>>)
	{
		return VariableBase::get<ValueType>(getConstPtr());
	}
	else
	{
		return VariableBase::get<ValueType>(getPtr());
	}
}

template <typename ValueType>
void StaticField::set(ValueType&& data) const
{
	VariableBase::set(getPtr(), std::forward<ValueType>(data));
}