/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename EntityType, typename ContainerType>
bool EntityUtility::foreachEntity(ContainerType const& container, Visitor<EntityType> visitor, void* userData) noexcept
{
	if (visitor != nullptr)
	{
		for (EntityType const& entity : container)
		{
			if (!visitor(entity, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

template <typename EntityType, typename ContainerType>
bool EntityUtility::foreachEntityPtr(ContainerType const& container, Visitor<EntityType> visitor, void* userData) noexcept
{
	if (visitor != nullptr)
	{
		for (EntityType const* entity : container)
		{
			if (!visitor(*entity, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

template <typename ContainerType, typename Predicate>
typename ContainerType::value_type const* EntityUtility::getEntityByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) noexcept
{
	Entity::EntityImpl	searchedImpl(name, 0u);
	Entity				searchedEntity(&searchedImpl);

	typename ContainerType::const_iterator it = container.find(static_cast<typename ContainerType::value_type const&>(searchedEntity));

	//When deleted, the Entity will try to delete the implementation pointer.
	//As the implementation was not dynamically newed (to save perf), it crashes here.
	//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
	searchedEntity._pimpl.uncheckedSet(nullptr);

	return (it != container.cend() && predicate(*it)) ? *it : nullptr;
}

template <typename ContainerType, typename Predicate>
typename ContainerType::value_type EntityUtility::getEntityPtrByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) noexcept
{
	Entity::EntityImpl	searchedImpl(name, 0u);
	Entity				searchedEntity(&searchedImpl);

	typename ContainerType::const_iterator it = container.find(reinterpret_cast<typename ContainerType::value_type>(&searchedEntity));

	//When deleted, the Entity will try to delete the implementation pointer.
	//As the implementation was not dynamically newed (to save perf), it crashes here.
	//To avoid that, we force set the implementation to nullptr without deleting the previous one before entering ~Entity.
	searchedEntity._pimpl.uncheckedSet(nullptr);

	return (it != container.cend() && predicate(*it)) ? *it : nullptr;
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

template <typename ContainerType, typename Visitor>
bool EntityUtility::foreachEntityPtrNamed(ContainerType const& container, char const* name, Visitor visitor)
{
	Entity::EntityImpl	searchedImpl(name, 0u);
	Entity				searchedEntity(&searchedImpl);

	auto range = container.equal_range(reinterpret_cast<typename ContainerType::value_type>(&searchedEntity));

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