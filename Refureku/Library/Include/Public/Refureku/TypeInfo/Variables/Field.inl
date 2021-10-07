/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ValueType>
ValueType Field::get(void* instance) const
{
	return FieldBase::get<ValueType>(getPtr(instance));
}

template <typename ValueType>
ValueType const Field::get(void const* instance) const noexcept
{
	static_assert(!std::is_rvalue_reference_v<ValueType>, "Can't call Field::get with an rvalue reference ValueType from a const instance.");

	return FieldBase::get<ValueType>(const_cast<void*>(getConstPtr(instance)));
}

template <typename ValueType>
void Field::set(void* instance, ValueType&& value) const
{
	FieldBase::set(getPtr(instance), std::forward<ValueType>(value));
}