/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ParentClass, typename ChildClass>
constexpr void CodeGenerationHelpers::registerChildClass(rfk::Struct& childClass) noexcept
{
	static_assert(std::is_class_v<ParentClass>, "registerChildClass first template argument must be a class.");
	static_assert(std::is_class_v<ChildClass>, "registerChildClass second template argument must be a class.");

	if constexpr (implements_template1__registerChildClass<ParentClass, ChildClass, void(rfk::Struct&)>::value)
	{
		ParentClass::template _registerChildClass<ChildClass>(childClass);
	}
}