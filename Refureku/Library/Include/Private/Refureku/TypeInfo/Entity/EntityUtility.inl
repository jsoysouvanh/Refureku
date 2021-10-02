/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename EntityType, typename ContainerType>
bool EntityUtility::foreachEntity(ContainerType const& container, bool (*visitor)(EntityType const&, void*), void* userData) noexcept
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
bool EntityUtility::foreachEntityPtr(ContainerType const& container, bool (*visitor)(EntityType const&, void*), void* userData) noexcept
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
	EntityAPI::EntityImpl	searchedImpl(name, 0u);

	typename ContainerType::const_iterator it = container.find(static_cast<typename ContainerType::value_type&&>(EntityAPI(&searchedImpl)));

	return (it != container.cend() && predicate(*it)) ? *it : nullptr;
}

template <typename ContainerType, typename Predicate>
typename ContainerType::value_type EntityUtility::getEntityPtrByNameAndPredicate(ContainerType const& container, char const* name, Predicate predicate) noexcept
{
	EntityAPI::EntityImpl	searchedImpl(name, 0u);
	EntityAPI				searchedEntity(&searchedImpl);

	typename ContainerType::const_iterator it = container.find(reinterpret_cast<typename ContainerType::value_type>(&searchedEntity));

	return (it != container.cend() && predicate(*it)) ? *it : nullptr;
}

template <typename ContainerType, typename Visitor>
bool EntityUtility::foreachEntityNamed(ContainerType const& container, char const* name, Visitor visitor)
{
	EntityAPI::EntityImpl searchedImpl(name, 0u);

	auto range = container.equal_range(static_cast<typename ContainerType::value_type&&>(EntityAPI(&searchedImpl)));

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
	EntityAPI::EntityImpl	searchedImpl(name, 0u);
	EntityAPI				searchedEntity(&searchedImpl);

	auto range = container.equal_range(reinterpret_cast<typename ContainerType::value_type>(&searchedEntity));

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
	EntityAPI::EntityImpl	searchedImpl("", id);
	EntityAPI				searchedEntity(&searchedImpl);

	auto it = container.find(&searchedEntity);

	return (it != container.cend()) ? *it : nullptr;
}