/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename DataType>
DataType StaticField::getData() const noexcept
{
	if constexpr (std::is_rvalue_reference_v<DataType>)
	{
		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(getDataAddress()));
	}
	else if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		return *reinterpret_cast<std::remove_reference_t<DataType>*>(getDataAddress());
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(getDataAddress()));
	}
}

template <typename DataType>
void StaticField::setData(DataType&& data) const noexcept
{
	if constexpr (std::is_rvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<DataType*>(getDataAddress()) = std::forward<DataType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<DataType&&>*>(getDataAddress()) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}

inline void* StaticField::getDataAddress() const noexcept
{
	return dataAddress;
}

inline void StaticField::setData(void const* data, uint64 dataSize) const noexcept
{
	std::memcpy(getDataAddress(), data, dataSize);
}