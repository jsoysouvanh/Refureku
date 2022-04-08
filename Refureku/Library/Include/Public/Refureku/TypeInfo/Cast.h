/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits> //std::is_class_v, is_base_of_v

#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/Misc/CopyConstness.h"
#include "Refureku/Misc/TypeTraitsMacros.h"
#include "Refureku/Object.h"

namespace rfk
{
	/**
	*	@brief	Adjust the pointer of the provided instance of type fromArchetype to a pointer to a toArchetype.
	*	
	*	@tparam TargetClassType Type of pointer the result should be cast to. To get a void*, call dynamicCast<void>(...).
	* 
	*	@param instance			Pointer to the instance to cast.
	*	@param fromArchetype	Archetype of the instance. If fromArchetype is not the concrete archetype of the provided instance, the behaviour is undefined.
	*	@param toArchetype		Archetype to cast instance to.
	* 
	*	@return A pointer to the adjusted instance if the cast was successful, else nullptr.
	*/
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
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<typename CopyConstness<TargetClassType, uint8>::Type*>(instance) - pointerOffset);
		}

		return nullptr;
	}

	/**
	*	@brief	Adjust the pointer of the provided instance of type fromArchetype to a pointer to a toArchetype.
	*			This method only works for upcast, which means that if fromArchetype is a parent class of toArchetype, nullptr is returned.
	*			Since the method checks only for upcast, it is theoritically faster than dynamicCast.
	*	
	*	@tparam TargetClassType Type of pointer the result should be cast to. To get a void*, call dynamicCast<void>(...).
	* 
	*	@param instance			Pointer to the instance to cast.
	*	@param fromArchetype	Archetype of the instance. If fromArchetype is not the concrete archetype of the provided instance, the behaviour is undefined.
	*	@param toArchetype		Archetype to cast instance to.
	* 
	*	@return A pointer to the adjusted instance if the upcast was successful, else nullptr.
	*/
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicUpCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		//If both both source and target types have the same archetype, there's no offset to perform
		if (fromArchetype == toArchetype)
		{
			return reinterpret_cast<TargetClassType*>(instance);
		}

		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		//instance != nullptr is check in 2nd because it is not likely to happen a lot
		if (toArchetype.getSubclassPointerOffset(fromArchetype, pointerOffset) && instance != nullptr)
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<typename CopyConstness<TargetClassType, uint8>::Type*>(instance) + pointerOffset);
		}

		return nullptr;
	}

	/**
	*	@brief	Adjust the pointer of the provided instance of type fromArchetype to a pointer to a toArchetype.
	*			This method only works for downcast, which means that if toArchetype is a parent class of fromArchetype, nullptr is returned.
	*			Since the method checks only for downcast, it is theoritically faster than dynamicCast.
	*	
	*	@tparam TargetClassType Type of pointer the result should be cast to. To get a void*, call dynamicCast<void>(...).
	* 
	*	@param instance			Pointer to the instance to cast.
	*	@param fromArchetype	Archetype of the instance. If fromArchetype is not the concrete archetype of the provided instance, the behaviour is undefined.
	*	@param toArchetype		Archetype to cast instance to.
	* 
	*	@return A pointer to the adjusted instance if the downcast was successful, else nullptr.
	*/
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType* dynamicDownCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype)
	{
		//If both both source and target types have the same archetype, there's no offset to perform
		if (fromArchetype == toArchetype)
		{
			return reinterpret_cast<TargetClassType*>(instance);
		}

		std::ptrdiff_t pointerOffset;

		//Get the memory offset
		//instance != nullptr is check in 2nd because it is not likely to happen a lot
		if (fromArchetype.getSubclassPointerOffset(toArchetype, pointerOffset) && instance != nullptr)
		{
			return reinterpret_cast<TargetClassType*>(reinterpret_cast<typename CopyConstness<TargetClassType, uint8>::Type*>(instance) - pointerOffset);
		}

		return nullptr;
	}

	RFK_GENERATE_IMPLEMENTS_METHOD_TRAITS(staticGetArchetype);

	/**
	*	@brief	Downcast the provided class instance to a more concrete class type if possible.
	*			The provided instance must inherit from rfk::Object in order to retrieve its concrete archetype.
	* 
	*	@param instance The instance to cast. It must inherit from rfk::Object.
	* 
	*	@return The casted instance if successful, else nullptr.
	*/
	template <typename TargetClassType, typename SourceClassType>
	RFK_NODISCARD TargetClassType* dynamicCast(SourceClassType* instance)
	{
		static_assert(std::is_class_v<SourceClassType> && std::is_class_v<TargetClassType>, "[Refureku] Can't use dynamicCast with non-class types.");
		static_assert(!std::is_base_of_v<TargetClassType, SourceClassType>, "[Refureku] Don't use dynamicCast to perform a simple upcast. Use implicit conversion or static_cast instead.");
		static_assert(!std::is_same_v<SourceClassType, TargetClassType>, "[Refureku] Don't use dynamicCast to cast to the source type itself.");
		static_assert(std::is_base_of_v<rfk::Object, SourceClassType>, "[Refureku] Can't use dynamicCast if instance doesn't inherit from rfk::Object.");

		/**
		*	dynamicCast requires TargetClassType to implement the staticGetArchetype method, so
		*	TargetClassType must be reflected by rfk generator system for this dynamicCast to work.
		*	By the assumptions we made beforehand, there are no real valid reason not to reflect TargetClassType with Refureku since:
		*		1. SourceClassType must inherit from rfk::Object (and therefore is likely reflected using Refureku)
		*		2. SourceClassType is a base class of TargetClassType (since we perform a downcast... for an upcast an implicit compile-time static_cast does the job)
		* 
		*	To generate comprehensible errors, we still check at compile-time that TargetClassType indeed implements staticGetArchetype:
		*/
		static_assert(implements_staticGetArchetype<TargetClassType, Struct const&()>::value, "[Refureku] The target class must implement the staticGetArchetype method.");

		rfk::Struct const& instanceConcreteType = instance->getArchetype();

		//TODO: Optimization if single inheritance: don't perform this intermediate computation

		auto intermediatePtr = dynamicDownCast<typename CopyConstness<SourceClassType, void>::Type>(
			reinterpret_cast<typename CopyConstness<SourceClassType, void>::Type*>(instance),
			SourceClassType::staticGetArchetype(),
			instanceConcreteType
		);

		// --------------------------------------------------------------------

		//Try to upcast the concrete type of instance to TargetClassType
		return (intermediatePtr != nullptr) ?
			dynamicUpCast<TargetClassType>(intermediatePtr, instanceConcreteType, TargetClassType::staticGetArchetype()) :
			nullptr;
	}
}