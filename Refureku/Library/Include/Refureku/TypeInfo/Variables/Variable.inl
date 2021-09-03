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
		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(_address));
	}
	else if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		return *reinterpret_cast<std::remove_reference_t<DataType>*>(_address);
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(_address));
	}
}

template <typename DataType>
void Variable::setData(DataType&& data) const
{
	if (type.isConst())
	{
		throw ConstViolation("Can't use Variable::setData on a const variable.");
	}

	if constexpr (std::is_rvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<DataType*>(_address) = std::forward<DataType&&>(data);
	}
	else if constexpr (std::is_lvalue_reference_v<DataType&&>)
	{
		*reinterpret_cast<std::remove_reference_t<DataType&&>*>(_address) = data;
	}
	else
	{
		assert(false);	//How can we get here?
	}
}

inline void Variable::setData(void const* data, uint64 dataSize) const
{
	if (type.isConst())
	{
		throw ConstViolation("Can't use Variable::setData on a const variable.");
	}

	std::memcpy(_address, data, dataSize);
}