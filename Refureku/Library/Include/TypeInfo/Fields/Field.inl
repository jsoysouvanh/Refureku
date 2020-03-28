
template <typename DataType>
DataType Field::getData(void* instance) const noexcept
{
	return *reinterpret_cast<DataType*>(getDataAddress(instance));
}

/**
*	Set the data corresponding to this field in the provided instance
*/
template <typename T>
void Field::setData(void* instance, T&& data) const noexcept
{
	//TODO
}