
template <typename DataType>
DataType Field::getData(void* instance) const noexcept
{
	if constexpr (std::is_rvalue_reference_v<DataType>)
	{
		return std::move(*reinterpret_cast<std::remove_reference_t<DataType>*>(getDataAddress(instance)));
	}
	else if constexpr (std::is_lvalue_reference_v<DataType>)
	{
		return *reinterpret_cast<std::remove_reference_t<DataType>*>(getDataAddress(instance));
	}
	else	//By value
	{
		return DataType(*reinterpret_cast<DataType*>(getDataAddress(instance)));
	}
}

template <typename DataType>
void Field::setData(void* instance, DataType&& data) const noexcept
{
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

inline void* Field::getDataAddress(void* instance) const noexcept
{
	return reinterpret_cast<char*>(instance) + memoryOffset;
}

inline void Field::setData(void* instance, void const* data, uint64 dataSize) const noexcept
{
	std::memcpy(getDataAddress(instance), data, dataSize);
}