
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

/**
*	Set the data corresponding to this field in the provided instance
*/
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