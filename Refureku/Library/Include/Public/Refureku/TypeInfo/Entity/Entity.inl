/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename PropertyType, typename>
PropertyType const* Entity::getProperty(bool isChildClassValid) const noexcept
{
	//Not safe if PropertyType inherits from multiple polymorphic types and rfk::Property is not the first inherited type
	//Specified in method documentation.
	return reinterpret_cast<PropertyType const*>(getProperty(PropertyType::staticGetArchetype(), isChildClassValid));
}

template <typename PropertyType, typename>
Vector<PropertyType const*> Entity::getProperties(bool isChildClassValid) const noexcept
{
	static_assert(std::is_base_of_v<Property, PropertyType>, "Can't call Entity::getProperty<> with a class that is not a subclass of rfk::Property.");

	//Not safe if PropertyType inherits from multiple polymorphic types and rfk::Property is not the first inherited type
	//Specified in method documentation.
	return getProperties(PropertyType::staticGetArchetype(), isChildClassValid);
}