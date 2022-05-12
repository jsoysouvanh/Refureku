/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename T>
Archetype const* getArchetype() noexcept
{
	//Eliminate all unsupported types first
	if constexpr (std::is_function_v<T> || std::is_member_object_pointer_v<T>)
	{
		return nullptr;
	}
	else
	{
		//Get rid of cv-qualifiers, array, and references
		using RawType = std::decay_t<T>;

		if constexpr (std::is_pointer_v<RawType>)
		{
			return getArchetype<std::remove_pointer_t<RawType>>();
		}
		else if constexpr (std::is_class_v<RawType>)
		{
			if constexpr (std::is_const_v<T> || std::is_volatile_v<T> || std::is_reference_v<T>)
			{
				return getArchetype<RawType>();
			}
			else if constexpr (internal::isCallable_static_staticGetArchetype<T, Archetype const&()>::value)
			{
				return &T::staticGetArchetype();
			}
			else
			{
				return nullptr;
			}
		}
		else if constexpr (std::is_enum_v<RawType>)
		{
			return getEnum<RawType>();
		}
		else
		{
			return nullptr;
		}
	}
}

template <template <typename...> typename T>
Archetype const* getArchetype() noexcept
{
	return nullptr;
}

template <template <auto...> typename T>
Archetype const* getArchetype() noexcept
{
	return nullptr;
}

#if RFK_TEMPLATE_TEMPLATE_SUPPORT

template <template <template <typename...> typename...> typename T>
Archetype const* getArchetype() noexcept
{
	return nullptr;
}

#endif