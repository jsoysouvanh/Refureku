/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits> //std::is_class_v

#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/Misc/CopyConstness.h"

namespace rfk
{
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		//If both both source and target types have the same archetype, there's no offset to perform
		if (fromArchetype == toArchetype)
		{
			return reinterpret_cast<TargetClassType*>(instance);
		}

		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		//instance != nullptr is check in 2nd because it is not likely to happen a lot
		if (fromArchetype.getPointerOffset(toArchetype, pointerOffset) && instance != nullptr)
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<CopyConstness<TargetClassType, uint8>::Type*>(instance) - pointerOffset);
		}

		return nullptr;
	}

	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicUpCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		//instance != nullptr is check in 2nd because it is not likely to happen a lot
		if (toArchetype.getSubclassPointerOffset(fromArchetype, pointerOffset) && instance != nullptr)
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<CopyConstness<TargetClassType, uint8>::Type*>(instance) + pointerOffset);
		}

		return nullptr;
	}

	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicDownCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		//instance != nullptr is check in 2nd because it is not likely to happen a lot
		if (fromArchetype.getSubclassPointerOffset(toArchetype, pointerOffset) && instance != nullptr)
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<CopyConstness<TargetClassType, uint8>::Type*>(instance) - pointerOffset);
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