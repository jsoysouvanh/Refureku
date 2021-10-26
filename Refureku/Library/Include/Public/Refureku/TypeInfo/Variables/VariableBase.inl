/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ValueType>
ValueType VariableBase::get(void* ptr) const
{
	static_assert(!std::is_const_v<std::remove_reference_t<ValueType>>, "VariableBase::get with const lvalue ref should be handled by the VariableBase::get(void const*) overload.");

	if constexpr (std::is_rvalue_reference_v<ValueType>)
	{
		assert(!getType().isConst());

		return std::move(*reinterpret_cast<std::remove_reference_t<ValueType>*>(ptr));
	}
	else if constexpr (std::is_lvalue_reference_v<ValueType>)
	{
		assert(!getType().isConst());

		return *reinterpret_cast<std::remove_reference_t<ValueType>*>(ptr);
	}
	else	//By value
	{
		return get<ValueType>(reinterpret_cast<void const*>(ptr));
	}
}

template <typename ValueType>
ValueType VariableBase::get(void const* ptr) const
{
	static_assert(!std::is_rvalue_reference_v<ValueType>, "Can't call VariableBase::get(void const*) with rvalue type.");

	if constexpr (std::is_lvalue_reference_v<ValueType>)
	{
		static_assert(std::is_const_v<std::remove_reference_t<ValueType>>, "Can't call VariableBase::get(void const*) with non-const lvalue type.");

		return *reinterpret_cast<std::remove_reference_t<ValueType>*>(ptr);
	}
	else
	{
		static_assert(VariableBase::is_value_v<ValueType>);	//At this point, should be a value type

		return ValueType(*reinterpret_cast<ValueType const*>(ptr));
	}
}

template <typename ValueType>
void VariableBase::set(void* ptr, ValueType&& value) const
{
	assert(!getType().isConst());

	if constexpr (std::is_rvalue_reference_v<ValueType&&>)
	{
		*reinterpret_cast<ValueType*>(ptr) = std::forward<ValueType&&>(value);
	}
	else if constexpr (std::is_lvalue_reference_v<ValueType&&>)
	{
		*reinterpret_cast<std::remove_const_t<std::remove_reference_t<ValueType&&>>*>(ptr) = value;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}