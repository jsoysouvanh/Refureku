/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename DataType>
DataType StaticField::getData() const
{
	if constexpr (std::is_rvalue_reference_v<DataType>)
	{
		if (getType().isConst())
		{
			throw ConstViolation("StaticField::getData can't be called with an rvalue DataType on const static fields.");
		}

		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(getAddress()));
	}
	else if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		if (getType().isConst())
		{
			if constexpr (!std::is_const_v<std::remove_reference_t<DataType>>)
			{
				throw ConstViolation("StaticField::getData can't be called with an non-const reference DataType on const static fields.");
			}
		}

		return *reinterpret_cast<std::remove_reference_t<DataType>*>(getAddress());
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(getAddress()));
	}
}

template <typename DataType>
void StaticField::setData(DataType&& data) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call StaticField::setData on a const static field.");
	}

	if constexpr (std::is_rvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<DataType*>(getAddress()) = std::forward<DataType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<DataType&&>*>(getAddress()) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}

inline void StaticField::setData(void const* data, uint64 dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call StaticField::setData on a const static field.");
	}

	std::memcpy(getAddress(), data, dataSize);
}

inline void* StaticField::getAddress() const noexcept
{
	return _address;
}