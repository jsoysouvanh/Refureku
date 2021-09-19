/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename PropertyType, typename>
PropertyType const* Entity::getProperty(bool isChildClassValid) const noexcept
{
	return reinterpret_cast<PropertyType const*>(getProperty(PropertyType::staticGetArchetype(), isChildClassValid));
}

template <typename Predicate, typename>
Property const* Entity::getProperty(Predicate predicate) const
{
	for (Property const* property : _properties)
	{
		if (predicate(property))
		{
			return property;
		}
	}

	return nullptr;
}

template <typename PropertyType, typename>
std::vector<PropertyType const*> Entity::getProperties(bool isChildClassValid) const noexcept
{
	std::vector<Property const*> result = getProperties(PropertyType::staticGetArchetype(), isChildClassValid);

	return reinterpret_cast<std::vector<PropertyType const*>&>(result);
}

template <typename Predicate, typename>
std::vector<Property const*> Entity::getProperties(Predicate predicate) const
{
	std::vector<Property const*> result;

	for (Property const* property : _properties)
	{
		if (predicate(property))
		{
			result.emplace_back(property);
		}
	}

	return result;
}

inline bool Entity::operator==(Entity const& other) const noexcept
{
	//2 entities are equal if they have the same address
	return &other == this;
}

inline bool Entity::operator!=(Entity const& other) const noexcept
{
	return &other != this;
}