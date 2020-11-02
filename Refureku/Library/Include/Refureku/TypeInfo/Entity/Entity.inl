/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename PropertyType, typename>
PropertyType const* Entity::getProperty() const noexcept
{
	static_assert(!std::is_abstract_v<PropertyType>, "Can't get an abstract property.");

	Struct const* queriedPropertyArchetype = &PropertyType::staticGetArchetype();

	//Iterate over all props to find a matching property
	for (Property const* p : properties)
	{
		if (queriedPropertyArchetype == &p->getArchetype())
		{
			return reinterpret_cast<PropertyType const*>(p);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Property const* Entity::getProperty(Predicate predicate) const
{
	for (Property const* property : properties)
	{
		if (predicate(property))
		{
			return property;
		}
	}

	return nullptr;
}

template <typename PropertyType, typename>
std::vector<PropertyType const*> Entity::getProperties() const noexcept
{
	static_assert(!std::is_abstract_v<PropertyType>, "Can't get an abstract property.");

	std::vector<PropertyType const*> result;

	Struct const* queriedPropertyArchetype = &PropertyType::staticGetArchetype();

	//Iterate over all props to find a matching property
	for (Property const* p : properties)
	{
		if (queriedPropertyArchetype == &p->getArchetype())
		{
			result.emplace_back(reinterpret_cast<PropertyType const*>(p));
		}
	}

	return result;
}

template <typename Predicate, typename>
std::vector<Property const*> Entity::getProperties(Predicate predicate) const
{
	std::vector<Property const*> result;

	for (Property const* property : properties)
	{
		if (predicate(property))
		{
			result.emplace_back(property);
		}
	}

	return result;
}