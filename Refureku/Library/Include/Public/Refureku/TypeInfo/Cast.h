/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits> //std::is_class_v

#include "Refureku/TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicCast(void* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		//If both both source and target types have the same archetype, there's no offset to perform
		if (fromArchetype == toArchetype)
		{
			return reinterpret_cast<TargetClassType*>(instance);
		}

		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		if (instance != nullptr && fromArchetype.getPointerOffset(toArchetype, pointerOffset))
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<uint8*>(instance) - pointerOffset);
		}

		return nullptr;
	}

	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicUpCast(void* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		if (instance != nullptr && toArchetype.getSubclassPointerOffset(fromArchetype, pointerOffset))
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<uint8*>(instance) + pointerOffset);
		}

		return nullptr;
	}

	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicDownCast(void* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		//Since we only consider down casts, 
		if (instance != nullptr && fromArchetype.getSubclassPointerOffset(toArchetype, pointerOffset))
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<uint8*>(instance) - pointerOffset);
		}

		return nullptr;
	}

	/**
	*	@brief	Downcast the provided class instance to a more concrete class type if possible.
	*			Both SourceClassType and TargetClassType must be reflected classes to use this method.
	* 
	*	@param instance The instance to cast.
	* 
	*	@return The casted instance if successful, else nullptr.
	* 
	*	@exception NotReflectedStructException TODO if SourceClassType or TargetClassType (or both) is not a reflected class.
	*/
	template <typename TargetClassType, typename SourceClassType>
	RFK_NODISCARD TargetClassType* dynamicCast(SourceClassType* instance)
	{
		static_assert(std::is_class_v<SourceClassType> && std::is_class_v<TargetClassType>, "Can't use dynamicCast with non-class types.");
		static_assert(std::is_base_of_v<SourceClassType, TargetClassType> && std::is_same_v<SourceClassType, TargetClassType>, "Don't use dynamicCast if you want to perform a simple upcast.");

		Struct const* fromArchetype = static_cast<Struct const*>(getArchetype<SourceClassType>());
		Struct const* toArchetype = static_cast<Struct const*>(getArchetype<TargetClassType>());

		//Perform cast only if both classes are reflected
		if (fromArchetype != nullptr && toArchetype != nullptr)
		{
			return dynamicDownCast<TargetClassType>(instance, *fromArchetype, *toArchetype);
		}
		else
		{
			throw 1; //TODO
		}
	}

	template <typename TargetClassType, typename SourceClassType>
	RFK_NODISCARD TargetClassType& dynamicCast(SourceClassType& instance)
	{
		TargetClassType* result = dynamicCast<TargetClassType, SourceClassType>(&instance);

		if (result != nullptr)
		{
			return *result;
		}
		else
		{
			throw 1; //TODO
		}
	}
}