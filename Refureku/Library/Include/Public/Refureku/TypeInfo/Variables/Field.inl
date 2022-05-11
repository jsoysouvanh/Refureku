/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ValueType, typename OwnerStructType, typename>
ValueType Field::get(OwnerStructType& instance) const
{
	//TODO: Add pointer adjustment and forward the adjusted pointer to getInternal
	return getInternal<ValueType>(&instance);
}

template <typename ValueType>
ValueType Field::getUnsafe(void* instance) const
{
	return getInternal<ValueType>(instance);
}

template <typename ValueType>
ValueType Field::getInternal(void* instance) const
{
	if constexpr (VariableBase::is_value_v<ValueType> || std::is_const_v<std::remove_reference_t<ValueType>>)
	{
		return FieldBase::get<ValueType>(getConstPtrInternal(instance));
	}
	else
	{
		return FieldBase::get<ValueType>(getPtrInternal(instance));
	}
}

template <typename ValueType, typename OwnerStructType, typename>
ValueType Field::get(OwnerStructType const& instance) const
{
	//TODO: Add pointer adjustment and forward the adjusted pointer to getInternal
	return getInternal<ValueType>(&instance);
}

template <typename ValueType>
ValueType Field::getUnsafe(void const* instance) const
{
	return getInternal<ValueType>(instance);
}

template <typename ValueType>
ValueType const Field::getInternal(void const* instance) const noexcept
{
	static_assert(!std::is_rvalue_reference_v<ValueType>, "Can't call Field::get with an rvalue reference ValueType from a const instance.");

	return FieldBase::get<ValueType>(getConstPtrInternal(instance));
}

template <typename ValueType, typename OwnerStructType, typename>
void Field::set(OwnerStructType& instance, ValueType&& value) const
{
	//TODO: Add pointer adjustment and forward the adjusted pointer to getInternal
	setInternal<ValueType>(&instance, std::forward<ValueType>(value));
}

template <typename ValueType>
void Field::setUnsafe(void* instance, ValueType&& value) const
{
	setInternal<ValueType>(instance, std::forward<ValueType>(value));
}

template <typename ValueType>
void Field::setInternal(void* instance, ValueType&& value) const
{
	FieldBase::set(getPtrInternal(instance), std::forward<ValueType>(value));
}

template <typename OwnerStructType, typename>
void Field::set(OwnerStructType& instance, void const* valuePtr, std::size_t valueSize) const
{
	//TODO: Add pointer adjustment and forward the adjusted pointer to getInternal
	setInternal(&instance, valuePtr, valueSize);
}

template <typename OwnerStructType, typename>
void* Field::getPtr(OwnerStructType& instance) const
{
	return getPtrInternal(&instance);
}

template <typename OwnerStructType, typename>
void const* Field::getConstPtr(OwnerStructType const& instance) const noexcept
{
	return getConstPtrInternal(&instance);
}