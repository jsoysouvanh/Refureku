/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::size_t initialCapacity) noexcept:
	_data{nullptr},
	_size{0u},
	_capacity{0u}
{
	reserve(computeNewCapacity(initialCapacity));
}

template <typename T, typename Allocator>
template <typename U, typename UAlloc>
Vector<T, Allocator>::Vector(Vector<U, UAlloc>&& other) noexcept:
	_data{reinterpret_cast<T*>(other._data)},
	_size{other._size},
	_capacity{other._capacity}
{
	other._data		= nullptr;
	other._size		= 0u;
	other._capacity	= 0u;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector const& other):
	_data{nullptr},
	_size{0u},
	_capacity{0u}
{
	resize(other._size);

	copyElements(other.data(), data(), other._size);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other) noexcept:
	_data{other._data},
	_size{other._size},
	_capacity{other._capacity}
{
	other._data		= nullptr;
	other._size		= 0u;
	other._capacity	= 0u;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
	checkedDelete();
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::constructElements(T* from, std::size_t count)
{
	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::construct(_allocator, from + i);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::copyElements(T const* from, T* to, std::size_t count)
{
	static_assert(std::is_copy_constructible_v<T>, "Can't call copyElements on a non-copyable type T.");

	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::construct(_allocator, to + i, *(from + i));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::copyElementsReverse(T const* from, T* to, std::size_t count)
{
	static_assert(std::is_copy_constructible_v<T>, "Can't call copyElements on a non-copyable type T.");

	for (std::size_t i = 1; i <= count; i++)
	{
		AllocTraits::construct(_allocator, to + count - i, *(from + count - i));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::moveElements(T* from, T* to, std::size_t count)
{
	static_assert(std::is_move_constructible_v<T>, "Can't call moveElements on a non-moveable type T.");

	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::construct(_allocator, to + i, std::move(*(from + i)));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::moveElementsReverse(T* from, T* to, std::size_t count)
{
	static_assert(std::is_move_constructible_v<T>, "Can't call moveElements on a non-moveable type T.");

	for (std::size_t i = 1; i <= count; i++)
	{
		AllocTraits::construct(_allocator, to + count - i, std::move(*(from + count - i)));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::destroyElements(T* from, std::size_t count)
{
	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::destroy(_allocator, from + i);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::checkedDelete()
{
	if (_data != nullptr)
	{
		destroyElements(data(), _size);
		
		_allocator.deallocate(_data, _capacity);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reallocateIfNecessary(std::size_t minCapacity)
{
	if (minCapacity > _capacity)
	{
		reserve(computeNewCapacity(minCapacity));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::makeFreeSpaceForXElements(std::size_t index, std::size_t count)
{
	std::size_t newSize = size() + count;

	if (newSize > _capacity)
	{
		//Reallocate manually so that we don't remove elements avec reallocation
		std::size_t newCapacity = computeNewCapacity(newSize);
		T* newData = reinterpret_cast<T*>(_allocator.allocate(newCapacity));

		if (_data != nullptr)
		{
			//Move elements if possible
			if constexpr (std::is_move_constructible_v<T>)
			{
				//Move elements before the free space
				moveElements(data(), newData, index);

				//Move elements after the free space
				moveElements(data() + index, newData + index + count, _size - index);
			}
			else //Copy elements otherwise
			{
				copyElements(data(), newData, index);
				copyElements(data() + index, newData + index + count, _size - index);
			}

			destroyElements(data(), _size);

			//Release previously allocated memory
			_allocator.deallocate(_data, _capacity);
		}

		_data		= newData;
		_capacity	= newCapacity;
	}
	//Don't do anything if there's enough capacity to handle new elements and they are appended to the end of the vector
	else if (index != _size)
	{
		//Move elements if possible
		//Elements are moved/copied in reverse order to avoid memory overwrite in case the free space (count)
		//	is smaller than the number of elements to copy
		if constexpr (std::is_move_constructible_v<T>)
		{
			moveElementsReverse(data() + index, data() + index + count, _size - index);
		}
		else
		{
			copyElementsReverse(data() + index, data() + index + count, _size - index);
		}

		destroyElements(data() + index, count);
	}
}

template <typename T, typename Allocator>
std::size_t	Vector<T, Allocator>::computeNewCapacity(std::size_t minCapacity) const noexcept
{
	//TODO: Should handle the case when _capacity * _growthFactor > std::size_t max value
	std::size_t newCapacity = static_cast<std::size_t>(_capacity * _growthFactor);

	return (newCapacity > minCapacity) ? newCapacity : minCapacity;
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::front() noexcept
{
	assert(!empty());

	return *data();
}

template <typename T, typename Allocator>
T const& Vector<T, Allocator>::front() const noexcept
{
	assert(!empty());

	return *data();
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::back() noexcept
{
	assert(!empty());

	return *(data() + _size - 1);
}

template <typename T, typename Allocator>
T const& Vector<T, Allocator>::back() const noexcept
{
	assert(!empty());

	return *(data() + _size - 1);
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::data() noexcept
{
	return _data;
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::data() const noexcept
{
	return _data;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reserve(std::size_t capacity)
{
	if (capacity > _capacity)
	{
		T* newData = reinterpret_cast<T*>(_allocator.allocate(capacity));

		if (_data != nullptr)
		{
			//Move elements if possible
			if constexpr (std::is_move_constructible_v<T>)
			{
				moveElements(data(), newData, _size);
			}
			else //Copy elements otherwise
			{
				copyElements(data(), newData, _size);
			}

			destroyElements(data(), _size);

			//Release previously allocated memory
			_allocator.deallocate(_data, _capacity);
		}

		_data		= newData;
		_capacity	= capacity;
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(std::size_t size)
{
	if (size > _size)
	{
		reallocateIfNecessary(size);

		//Construct new elements
		constructElements(end(), size - _size);
	}
	else if (size < _size)
	{
		//Destroy overflowing elements
		destroyElements(end(), _size - size);
	}

	_size = size;
}

template <typename T, typename Allocator>
std::size_t	Vector<T, Allocator>::size() const noexcept
{
	return _size;
}

template <typename T, typename Allocator>
std::size_t Vector<T, Allocator>::capacity() const noexcept
{
	return _capacity;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const noexcept
{
	return _size == 0u;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::clear()
{
	destroyElements(data(), _size);

	_size = 0u;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(T const& value)
{
	reallocateIfNecessary(size() + 1u);

	AllocTraits::construct(_allocator, end(), value);
	_size++;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(T&& value)
{
	reallocateIfNecessary(size() + 1u);

	AllocTraits::construct(_allocator, end(), std::forward<T>(value));
	_size++;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(Vector const& other)
{
	if (!other.empty())
	{
		reallocateIfNecessary(size() + other.size());

		copyElements(other.cbegin(), end(), other.size());
		_size += other.size();
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(Vector&& other)
{
	if (!other.empty())
	{
		reallocateIfNecessary(size() + other.size());

		moveElements(other.begin(), end(), other.size());
		_size += other.size();
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::insert(std::size_t index, T const& element)
{
	makeFreeSpaceForXElements(index, 1u);

	AllocTraits::construct(_allocator, begin() + index, element);
	_size++;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::insert(std::size_t index, T&& element)
{
	makeFreeSpaceForXElements(index, 1u);

	AllocTraits::construct(_allocator, begin() + index, std::forward<T>(element));
	_size++;
}

template <typename T, typename Allocator>
template <typename... Args>
T& Vector<T, Allocator>::emplace_back(Args&&... args)
{
	reallocateIfNecessary(size() + 1u);

	AllocTraits::construct(_allocator, end(), std::forward<Args>(args)...);
	_size++;

	return back();
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::begin() noexcept
{
	return data();
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::begin() const noexcept
{
	return cbegin();
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::cbegin() const noexcept
{
	return data();
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::end() noexcept
{
	return data() + _size;
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::end() const noexcept
{
	return cend();
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::cend() const noexcept
{
	return data() + _size;
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](std::size_t index) noexcept
{
	return *(data() + index);
}

template <typename T, typename Allocator>
T const& Vector<T, Allocator>::operator[](std::size_t index) const noexcept
{
	return *(data() + index);
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector const& other)
{
	destroyElements(data(), _size);

	reallocateIfNecessary(other.size());

	copyElements(other.data(), data(), other.size());

	return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& other) noexcept
{
	checkedDelete();

	_data			= other._data;
	_size			= other._size;
	_capacity		= other._capacity;
	other._data		= nullptr;
	other._size		= 0u;
	other._capacity	= 0u;

	return *this;
}