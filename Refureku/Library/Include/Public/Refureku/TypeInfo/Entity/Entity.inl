/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename PropertyType>
PropertyType const* Entity::getProperty(bool isChildClassValid) const noexcept
{
	return reinterpret_cast<PropertyType const*>(getProperty(PropertyType::staticGetArchetype(), isChildClassValid));
}

template <typename PropertyType>
Vector<PropertyType const*> Entity::getProperties(bool isChildClassValid) const noexcept
{
	//Not safe if PropertyType inherits from multiple polymorphic types and rfk::Property is not the first inherited type
	//Specified in method documentation.
	return getProperties(PropertyType::staticGetArchetype(), isChildClassValid);
}