/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
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
			return nullptr;

			/*if constexpr (isReflectedClass<RawType>)
			{
				return &RawType::staticGetArchetype();
			}
			else
			{
				return nullptr;
			}*/
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