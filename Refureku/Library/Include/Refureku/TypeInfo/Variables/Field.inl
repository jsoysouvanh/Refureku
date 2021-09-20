/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename DataType>
DataType Field::getData(void* instance) const
{
	if constexpr (std::is_rvalue_reference_v<DataType>)
	{
		if (getType().isConst())
		{
			throw ConstViolation("Field::getData can't be called with an rvalue DataType on const fields.");
		}

		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(getDataAddress(instance)));
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

		return *reinterpret_cast<std::remove_reference_t<DataType>*>(getDataAddress(instance));
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(getDataAddress(instance)));
	}
}

template <typename DataType>
DataType const Field::getData(void const* instance) const noexcept
{
	static_assert(!std::is_rvalue_reference_v<DataType>, "Can't call Field::getData with an rvalue reference DataType from a const instance.");

	if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		return *reinterpret_cast<std::remove_reference_t<DataType> const*>(getDataAddress(instance));
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType const*>(getDataAddress(instance)));
	}
}

template <typename DataType>
void Field::setData(void* instance, DataType&& data) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call Field::setData on a const field.");
	}

	if constexpr (std::is_rvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<DataType*>(getDataAddress(instance)) = std::forward<DataType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<DataType&&>*>(getDataAddress(instance)) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}

inline void Field::setData(void* instance, void const* data, uint64 dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call Field::setData on a const field.");
	}

	std::memcpy(getDataAddress(instance), data, dataSize);
}

inline void* Field::getDataAddress(void* instance) const noexcept
{
	assert(instance != nullptr);

	return reinterpret_cast<uint8_t*>(instance) + getMemoryOffset();
}

inline void const* Field::getDataAddress(void const* instance) const noexcept
{
	return reinterpret_cast<uint8_t const*>(instance) + getMemoryOffset();
}

inline std::size_t Field::getMemoryOffset() const noexcept
{
	return _memoryOffset;
}