/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename EntityType, typename ContainerType>
bool EntityUtility::foreachEntity(ContainerType const& container, Visitor<EntityType> visitor, void* userData)
{
	if (visitor != nullptr)
	{
		if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
		{
			for (auto entity : container)
			{
				if (!visitor(*entity, userData))
				{
					return false;
				}
			}
		}
		else
		{
			for (EntityType const& entity : container)
			{
				if (!visitor(entity, userData))
				{
					return false;
				}
			}
		}

		return true;
	}

	return false;
}

template <typename ContainerType, typename EntityType>
EntityType const* EntityUtility::getEntityByPredicate(ContainerType const& container, Predicate<EntityType> predicate, void* userData)
{
	if (predicate != nullptr)
	{
		if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
		{
			for (auto entity : container)
			{
				if (predicate(*entity, userData))
				{
					return entity;
				}
			}
		}
		else
		{
			for (EntityType const& entity : container)
			{
				if (predicate(entity, userData))
				{
					return &entity;
				}
			}
		}
	}

	return nullptr;
}

template <typename ContainerType, typename EntityType>
Vector<EntityType const*> EntityUtility::getEntitiesByPredicate(ContainerType const& container, Predicate<EntityType> predicate, void* userData)
{
	//When calling this method, we expect to have at least 2 results, so preallocate memory to avoid reallocations.
	Vector<EntityType const*> result(2);

	if (predicate != nullptr)
	{
		if constexpr (std::is_pointer_v<typename ContainerType::value_type>)
		{
			for (auto entity : container)
			{
				if (predicate(*entity, userData))
				{
					result.push_back(entity);
				}
			}
		}
		else
		{
			for (EntityType const& entity : container)
			{
				if (predicate(entity, userData))
				{
					result.push_back(&entity);
				}
			}
		}
	}

	return result;
}

template <typename ContainerType>
auto EntityUtility::getEntityByName(ContainerType const& container, char const* name) noexcept -> typename std::remove_pointer_t<typename ContainerType::value_type> const*
{
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

template <typename ContainerType, typename Visitor>
bool EntityUtility::foreachEntityNamed(ContainerType const& container, char const* name, Visitor visitor)
{
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