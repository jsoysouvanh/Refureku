/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ContainerType, typename Visitor>
bool Algorithm::foreach(ContainerType const& container, Visitor visitor)
{
	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		for (auto entity : container)
		{
			if (!visitor(*entity))
			{
				return false;
			}
		}
	}
	else
	{
		for (auto const& entity : container)
		{
			if (!visitor(entity))
			{
				return false;
			}
		}
	}

	return true;
}

template <typename ItemType, typename ContainerType>
bool Algorithm::foreach(ContainerType const& container, Visitor<ItemType> visitor, void* userData)
{
	return (visitor != nullptr) ? foreach(container, [visitor, userData](ItemType const& entity) { return visitor(entity, userData); }) : false;
}

template <typename ContainerType, typename Predicate>
auto Algorithm::getItemByPredicate(ContainerType const& container, Predicate predicate) -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
{
	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		for (auto item : container)
		{
			if (predicate(*item))
			{
				return item;
			}
		}
	}
	else
	{
		for (auto const& item : container)
		{
			if (predicate(item))
			{
				return &item;
			}
		}
	}

	return nullptr;
}

template <typename ItemType, typename ContainerType>
ItemType const* Algorithm::getItemByPredicate(ContainerType const& container, Predicate<ItemType> predicate, void* userData)
{
	return (predicate != nullptr) ? getItemByPredicate(container, [predicate, userData](ItemType const& entity) { return predicate(entity, userData); }) : nullptr;
}

template <typename ContainerType, typename Predicate>
auto Algorithm::getItemsByPredicate(ContainerType const& container, Predicate predicate) -> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>
{
	//When calling this method, we expect to have at least 2 results, so preallocate memory to avoid reallocations.
	Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*> result(2);

	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		for (auto item : container)
		{
			if (predicate(*item))
			{
				result.push_back(item);
			}
		}
	}
	else
	{
		for (auto const& item : container)
		{
			if (predicate(item))
			{
				result.push_back(&item);
			}
		}
	}

	return result;
}

template <typename ItemType, typename ContainerType>
Vector<ItemType const*> Algorithm::getItemsByPredicate(ContainerType const& container, Predicate<ItemType> predicate, void* userData)
{
	if (predicate != nullptr)
	{
		return getItemsByPredicate(container, [predicate, userData](ItemType const& entity) { return predicate(entity, userData); });
	}
	else
	{
		return Vector<ItemType const*>(0);
	}
}

template <typename ContainerType, typename Predicate, typename Compare>
auto Algorithm::getSortedItemsByPredicate(ContainerType const& container, Predicate predicate, Compare compare) -> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>
{
	//When calling this method, we expect to have at least 2 results, so preallocate memory to avoid reallocations.
	Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*> result(2);

	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		for (auto item : container)
		{
			if (predicate(*item))
			{
				result.insert(Algorithm::getFirstGreaterElementIndex(result, item, compare), item);
			}
		}
	}
	else
	{
		for (auto const& item : container)
		{
			if (predicate(item))
			{
				result.insert(Algorithm::getFirstGreaterElementIndex(result, &item, compare), &item);
			}
		}
	}

	return result;
}

template <typename ContainerType>
auto Algorithm::getEntityByName(ContainerType const& container, char const* name) noexcept -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
{
	if (name == nullptr)
	{
		return nullptr;
	}

	Entity::EntityImpl	searchedImpl(name, 0u);
	Entity				searchedEntity(&searchedImpl);

	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		typename ContainerType::const_iterator it = container.find(reinterpret_cast<typename ContainerType::value_type>(&searchedEntity));

		//When deleted, the Entity will try to delete the implementation pointer.
		//As the implementation was not dynamically newed (to save perf), it crashes here.
		//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
		searchedEntity._pimpl.uncheckedSet(nullptr);

		return (it != container.cend()) ? *it : nullptr;
	}
	else
	{
		typename ContainerType::const_iterator it = container.find(reinterpret_cast<typename ContainerType::value_type const&>(searchedEntity));

		//When deleted, the Entity will try to delete the implementation pointer.
		//As the implementation was not dynamically newed (to save perf), it crashes here.
		//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
		searchedEntity._pimpl.uncheckedSet(nullptr);

		return (it != container.cend()) ? &*it : nullptr;
	}
}

template <typename ContainerType, typename Predicate>
auto Algorithm::getEntityByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
{
	auto result = Algorithm::getEntityByName(container, name);

	return (result != nullptr && predicate(*result)) ? result : nullptr;
}

template <typename ContainerType, typename Predicate>
auto Algorithm::getEntitiesByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) -> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>
{
	using ResultVector = Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>;

	if (name == nullptr)
	{
		return ResultVector();
	}

	//When calling this method, we expect to have at least 2 results, so preallocate memory to avoid reallocations.
	ResultVector result(2);

	Entity::EntityImpl	searchedImpl(name, 0u);
	Entity				searchedEntity(&searchedImpl);

	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		auto range = container.equal_range(static_cast<typename ContainerType::value_type>(&searchedEntity));

		//When deleted, the Entity will try to delete the implementation pointer.
		//As the implementation was not dynamically newed (to save perf), it crashes here.
		//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
		searchedEntity._pimpl.uncheckedSet(nullptr);

		for (auto it = range.first; it != range.second; it++)
		{
			if (predicate(**it))
			{
				result.push_back(*it);
			}
		}
	}
	else
	{
		auto range = container.equal_range(static_cast<typename ContainerType::value_type const&>(searchedEntity));

		//When deleted, the Entity will try to delete the implementation pointer.
		//As the implementation was not dynamically newed (to save perf), it crashes here.
		//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
		searchedEntity._pimpl.uncheckedSet(nullptr);

		for (auto it = range.first; it != range.second; it++)
		{
			if (predicate(*it))
			{
				result.push_back(&*it);
			}
		}
	}

	return result;
}

template <typename ContainerType, typename Visitor>
bool Algorithm::foreachEntityNamed(ContainerType const& container, char const* name, Visitor visitor)
{
	if (name == nullptr)
	{
		return false;
	}

	Entity::EntityImpl	searchedImpl(name, 0u);
	Entity				searchedEntity(&searchedImpl);

	auto range = container.equal_range(static_cast<typename ContainerType::value_type const&>(searchedEntity));

	//When deleted, the Entity will try to delete the implementation pointer.
	//As the implementation was not dynamically newed (to save perf), it crashes here.
	//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
	searchedEntity._pimpl.uncheckedSet(nullptr);

	for (auto it = range.first; it != range.second; it++)
	{
		if (!visitor(*it))
		{
			return false;
		}
	}

	return true;
}

template <typename ContainerType>
typename ContainerType::value_type Algorithm::getEntityPtrById(ContainerType const& container, std::size_t id) noexcept
{
	Entity::EntityImpl	searchedImpl("", id);
	Entity				searchedEntity(&searchedImpl);

	auto it = container.find(&searchedEntity);

	//When deleted, the Entity will try to delete the implementation pointer.
	//As the implementation was not dynamically newed (to save perf), it crashes here.
	//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
	searchedEntity._pimpl.uncheckedSet(nullptr);

	return (it != container.cend()) ? *it : nullptr;
}

template <typename ContainerType, typename Compare, typename ElementType, typename>
std::size_t Algorithm::getFirstGreaterElementIndex(ContainerType const& container, ElementType element, Compare compare) noexcept(noexcept(compare))
{
	for (std::size_t i = 0u; i < container.size(); i++)
	{
		if (compare(element, container[i]))
			return i;
	}

	return container.size();
}