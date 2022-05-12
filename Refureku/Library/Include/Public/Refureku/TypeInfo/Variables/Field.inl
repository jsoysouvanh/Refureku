/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ValueType, typename InstanceType, typename>
ValueType Field::get(InstanceType& instance) const
{
	return getUnsafe<ValueType>(adjustInstancePointerAddress(&instance));
}

template <typename ValueType>
ValueType Field::getUnsafe(void* instance) const
{
	if constexpr (VariableBase::is_value_v<ValueType> || std::is_const_v<std::remove_reference_t<ValueType>>)
	{
		return FieldBase::get<ValueType>(getConstPtrUnsafe(instance));
	}
	else
	{
		return FieldBase::get<ValueType>(getPtrUnsafe(instance));
	}
}

template <typename ValueType>
ValueType Field::getUnsafe(void const* instance) const
{
	static_assert(!std::is_rvalue_reference_v<ValueType>, "Can't call Field::get with an rvalue reference ValueType from a const instance.");

	return FieldBase::get<ValueType>(getConstPtrUnsafe(instance));
}

template <typename ValueType, typename InstanceType, typename>
void Field::set(InstanceType& instance, ValueType&& value) const
{
	setUnsafe<ValueType>(adjustInstancePointerAddress(&instance), std::forward<ValueType>(value));
}

template <typename ValueType>
void Field::setUnsafe(void* instance, ValueType&& value) const
{
	FieldBase::set(getPtrUnsafe(instance), std::forward<ValueType>(value));
}

template <typename InstanceType, typename>
void Field::set(InstanceType& instance, void const* valuePtr, std::size_t valueSize) const
{
	setUnsafe(adjustInstancePointerAddress(&instance), valuePtr, valueSize);
}

template <typename InstanceType, typename>
void* Field::getPtr(InstanceType& instance) const
{
	return getPtrUnsafe(adjustInstancePointerAddress(&instance));
}

template <typename InstanceType, typename>
void const* Field::getConstPtr(InstanceType const& instance) const
{
	return getConstPtrUnsafe(adjustInstancePointerAddress(&instance));
}

template <typename InstanceType>
InstanceType* Field::adjustInstancePointerAddress(InstanceType* instance) const
{
	Struct const& ownerStruct = *getOwner();

	if (ownerStruct != instance->getArchetype())
	{
		throw InvalidArchetype("The instance dynamic archetype must match the field's owner.");
	}

	//We are sure at this point that the targetArchetype is the instance dynamic archetype.
	//so we know InstanceType is a parent class of targetArchetype or targetArchetype itself.
	//In this situation, a single down cast should be enough.
	return rfk::dynamicDownCast<InstanceType>(instance, InstanceType::staticGetArchetype(), ownerStruct);
}