/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename DataType>
DataType Variable::getData() const noexcept
{
	if constexpr (std::is_rvalue_reference_v<DataType>)
	{
		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(address));
	}
	else if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		return *reinterpret_cast<std::remove_reference_t<DataType>*>(address);
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(address));
	}
}

template <typename DataType>
void Variable::setData(DataType&& data) const noexcept
{
	if constexpr (std::is_rvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<DataType*>(address) = std::forward<DataType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<DataType&&>*>(address) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}

inline void Variable::setData(void const* data, uint64 dataSize) const noexcept
{
	std::memcpy(address, data, dataSize);
}