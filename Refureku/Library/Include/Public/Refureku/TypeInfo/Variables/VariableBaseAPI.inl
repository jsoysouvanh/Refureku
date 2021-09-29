/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ValueType>
ValueType VariableBaseAPI::get(void* ptr) const
{
	if constexpr (std::is_rvalue_reference_v<ValueType>)
	{
		if (getType().isConst())
		{
			throwConstViolationException("VariableBase::get can't be called with an rvalue ValueType on const variables.");
		}

		return std::move(*reinterpret_cast<std::remove_reference_t<ValueType>*>(ptr));
	}
	else if constexpr (std::is_lvalue_reference_v<ValueType>)
	{
		if (getType().isConst())
		{
			if constexpr (!std::is_const_v<std::remove_reference_t<ValueType>>)
			{
				throwConstViolationException("VariableBase::get can't be called with an non-const reference ValueType on const variables.");
			}
		}

		return *reinterpret_cast<std::remove_reference_t<ValueType>*>(ptr);
	}
	else	//By value
	{
		return ValueType(*reinterpret_cast<ValueType*>(ptr));
	}
}

template <typename ValueType>
void VariableBaseAPI::set(void* ptr, ValueType&& data) const
{
	if (getType().isConst())
	{
		throwConstViolationException("VariableBase::set can't be called on const variables.");
	}

	if constexpr (std::is_rvalue_reference_v<ValueType&&>)
	{
		*reinterpret_cast<ValueType*>(ptr) = std::forward<ValueType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<ValueType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<ValueType&&>*>(ptr) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}