/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ContainerType, typename Visitor>
bool EntityUtility::foreachEntity(ContainerType const& container, Visitor visitor)
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

template <typename EntityType, typename ContainerType>
bool EntityUtility::foreachEntity(ContainerType const& container, Visitor<EntityType> visitor, void* userData)
{
	return (visitor != nullptr) ? foreachEntity(container, [visitor, userData](EntityType const& entity) { return visitor(entity, userData); }) : false;
}

template <typename ContainerType, typename Predicate>
auto EntityUtility::getEntityByPredicate(ContainerType const& container, Predicate predicate) -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
{
	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		for (auto entity : container)
		{
			if (predicate(*entity))
			{
				return entity;
			}
		}
	}
	else
	{
		for (auto const& entity : container)
		{
			if (predicate(entity))
			{
				return &entity;
			}
		}
	}

	return nullptr;
}

template <typename EntityType, typename ContainerType>
EntityType const* EntityUtility::getEntityByPredicate(ContainerType const& container, Predicate<EntityType> predicate, void* userData)
{
	return (predicate != nullptr) ? getEntityByPredicate(container, [predicate, userData](EntityType const& entity) { return predicate(entity, userData); }) : nullptr;
}

template <typename ContainerType, typename Predicate>
auto EntityUtility::getEntitiesByPredicate(ContainerType const& container, Predicate predicate) -> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>
{
	//When calling this method, we expect to have at least 2 results, so preallocate memory to avoid reallocations.
	Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*> result(2);

	if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
	{
		for (auto entity : container)
		{
			if (predicate(*entity))
			{
				result.push_back(entity);
			}
		}
	}
	else
	{
		for (auto const& entity : container)
		{
			if (predicate(entity))
			{
				result.push_back(&entity);
			}
		}
	}

	return result;
}

template <typename EntityType, typename ContainerType>
Vector<EntityType const*> EntityUtility::getEntitiesByPredicate(ContainerType const& container, Predicate<EntityType> predicate, void* userData)
{
	if (predicate != nullptr)
	{
		return getEntitiesByPredicate(container, [predicate, userData](EntityType const& entity) { return predicate(entity, userData); });
	}
	else
	{
		return Vector<EntityType const*>(0);
	}
}

template <typename ContainerType>
auto EntityUtility::getEntityByName(ContainerType const& container, char const* name) noexcept -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
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
auto EntityUtility::getEntityByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
{
	auto result = EntityUtility::getEntityByName(container, name);

	return (result != nullptr && predicate(*result)) ? result : nullptr;
}

template <typename ContainerType, typename Predicate>
auto EntityUtility::getEntitiesByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) -> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>
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
bool EntityUtility::foreachEntityNamed(ContainerType const& container, char const* name, Visitor visitor)
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
typename ContainerType::value_type EntityUtility::getEntityPtrById(ContainerType const& container, std::size_t id) noexcept
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