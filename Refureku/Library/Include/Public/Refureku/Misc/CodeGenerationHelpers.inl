/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename ParentClass, typename ChildClass>
constexpr void CodeGenerationHelpers::registerChildClass(rfk::Struct& childClass) noexcept
{
	static_assert(std::is_class_v<ParentClass>, "registerChildClass first template argument must be a class.");
	static_assert(std::is_class_v<ChildClass>, "registerChildClass second template argument must be a class.");

	//The 2nd template type is void because it is friended by all reflected classes
	//The traits would return false without the friend statement.
	if constexpr (implements_template1__rfk_registerChildClass<ParentClass, void, void(rfk::Struct&)>::value)
	{
		ParentClass::template _rfk_registerChildClass<ChildClass>(childClass);
	}
}

template <typename Derived, typename Base>
constexpr std::ptrdiff_t CodeGenerationHelpers::computeClassPointerOffset() noexcept
{
	static_assert(std::is_base_of_v<Base, Derived>, "Derived must be in Base inheritance tree (or must be Base itself).");

	Derived* derivedPtr = reinterpret_cast<Derived*>(1);
	Base* basePtr = static_cast<Base*>(derivedPtr);

	return reinterpret_cast<std::intptr_t>(basePtr) - reinterpret_cast<std::intptr_t>(derivedPtr);
}

template <typename ClassType>
std::size_t CodeGenerationHelpers::getReflectedFieldsCount() noexcept
{
	static_assert(std::is_class_v<ClassType>, "getReflectedFieldsCount template argument must be a class.");

	rfk::Struct const* archetype = reinterpret_cast<rfk::Struct const*>(rfk::getArchetype<ClassType>());

	return (archetype != nullptr) ? archetype->getFieldsCount() : 0u;
}

template <typename ClassType>
std::size_t CodeGenerationHelpers::getReflectedStaticFieldsCount() noexcept
{
	static_assert(std::is_class_v<ClassType>, "getReflectedStaticFieldsCount template argument must be a class.");

	rfk::Struct const* archetype = reinterpret_cast<rfk::Struct const*>(rfk::getArchetype<ClassType>());

	return (archetype != nullptr) ? archetype->getStaticFieldsCount() : 0u;
}

template <typename T>
rfk::SharedPtr<T> CodeGenerationHelpers::defaultSharedInstantiator()
#if !defined(__GNUC__) || defined (__clang__) || __GNUC__ > 9
	noexcept(!std::is_default_constructible_v<T> || std::is_nothrow_constructible_v<T>)
#endif
{
	if constexpr (std::is_default_constructible_v<T>)
	{
		return rfk::makeShared<T>();
	}
	else
	{
		return nullptr;
	}
}

template <typename T>
rfk::UniquePtr<T> CodeGenerationHelpers::defaultUniqueInstantiator()
#if !defined(__GNUC__) || defined (__clang__) || __GNUC__ > 9
noexcept(!std::is_default_constructible_v<T> || std::is_nothrow_constructible_v<T>)
#endif
{
	if constexpr (std::is_default_constructible_v<T>)
	{
		return rfk::makeUnique<T>();
	}
	else
	{
		return nullptr;
	}
}