/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename DataType>
DataType FieldAPI::getData(void* instance) const
{
	if constexpr (std::is_rvalue_reference_v<DataType>)
	{
		if (getType().isConst())
		{
			throw ConstViolation("Field::getData can't be called with an rvalue DataType on const fields.");
		}

		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(getDataPtr(instance)));
	}
	else if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		if (getType().isConst())
		{
			if constexpr (!std::is_const_v<std::remove_reference_t<DataType>>)
			{
				throw ConstViolation("Field::getData can't be called with an non-const reference DataType on const fields.");
			}
		}

		return *reinterpret_cast<std::remove_reference_t<DataType>*>(getDataPtr(instance));
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(getDataPtr(instance)));
	}
}

template <typename DataType>
DataType const FieldAPI::getData(void const* instance) const noexcept
{
	static_assert(!std::is_rvalue_reference_v<DataType>, "Can't call Field::getData with an rvalue reference DataType from a const instance.");

	if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		return *reinterpret_cast<std::remove_reference_t<DataType> const*>(getConstDataPtr(instance));
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType const*>(getConstDataPtr(instance)));
	}
}

template <typename DataType>
void FieldAPI::setData(void* instance, DataType&& data) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call Field::setData on a const field.");
	}

	if constexpr (std::is_rvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<DataType*>(getDataPtr(instance)) = std::forward<DataType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<DataType&&>*>(getDataPtr(instance)) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}