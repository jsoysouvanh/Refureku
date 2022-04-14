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
	namespace internal
	{
		RFK_GENERATE_IMPLEMENTS_METHOD_TRAITS(staticGetArchetype);
		RFK_GENERATE_IMPLEMENTS_METHOD_TRAITS(getArchetype);
	}

	/**
	*	@brief	Cast the provided class instance to another class type if possible.
	*			The provided instance must inherit from rfk::Object in order to retrieve its dynamic archetype.
	* 
	*	@param instance The instance to cast. It must inherit from rfk::Object.
	* 
	*	@return The casted instance if successful, else nullptr.
	*/
	template <typename TargetClassType, typename SourceClassType>
	RFK_NODISCARD TargetClassType*	dynamicCast(SourceClassType* instance)																noexcept;

	/**
	*	@brief	Adjust the pointer of the provided instance of a given static/dynamic type to a pointer to another target type if possible.
	* 
	*	@param instance					Pointer to the instance to cast.
	*	@param instanceStaticArchetype	The static archetype of the instance (the result of rfk::getArchetype<decltype(instance)>() before it was casted to void).
	*	@param instanceDynamicArchetype	The dynamic archetype of the instance (the result of instance->getArchetype(), overriden from rfk::Object).
	*	@param targetArchetype			The archetype of the target type.
	* 
	*	@return A pointer to the adjusted instance if the cast was successful, else nullptr.
	*/
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType*	dynamicCast(typename CopyConstness<TargetClassType, void>::Type*	instance,
												Struct const&											instanceStaticArchetype,
												Struct const&											instanceDynamicArchetype,
												Struct const&											targetArchetype)				noexcept;

	/**
	*	@brief	Adjust the pointer of the provided instance of type instanceStaticArchetype to a pointer to a targetArchetype.
	*			This method only works for upcast, which means that if instanceStaticArchetype is a parent class of targetArchetype, nullptr is returned.
	*			Since the method checks only for upcast, it is theoritically faster than dynamicCast.
	*	
	*	@tparam TargetClassType Type of pointer the result should be cast to. To get a void*, call dynamicCast<void>(...).
	* 
	*	@param instance					Pointer to the instance to cast.
	*	@param instanceStaticArchetype	Static archetype of the instance.
											If instanceStaticArchetype is not the static archetype of instance, the result of this method is UB.
	*	@param targetArchetype			Archetype to cast instance to.
	* 
	*	@return A pointer to the adjusted instance if the upcast was successful, else nullptr.
	*/
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType*	dynamicUpCast(typename CopyConstness<TargetClassType, void>::Type*	instance,
												  Struct const&											instanceStaticArchetype,
												  Struct const&											targetArchetype)				noexcept;

	/**
	*	@brief	Adjust the pointer of the provided instance of type instanceStaticArchetype to a pointer to a targetArchetype.
	*			This method only works for downcast, which means that if targetArchetype is a parent class of instanceStaticArchetype, nullptr is returned.
	*			Since the method checks only for downcast, it is theoritically faster than dynamicCast.
	*	
	*	@tparam TargetClassType Type of pointer the result should be cast to. To get a void*, call dynamicCast<void>(...).
	* 
	*	@param instance					Pointer to the instance to cast.
	*	@param instanceStaticArchetype	Static archetype of the instance. 
	*										If instanceStaticArchetype is not the static archetype of instance, the result of this method is UB.
	*	@param targetArchetype			Archetype to cast instance to.
	* 
	*	@return A pointer to the adjusted instance if the downcast was successful, else nullptr.
	*/
	template <typename TargetClassType>
	RFK_NODISCARD TargetClassType*	dynamicDownCast(typename CopyConstness<TargetClassType, void>::Type*	instance,
													Struct const&											instanceStaticArchetype,
													Struct const&											targetArchetype)			noexcept;

	#include "Refureku/TypeInfo/Cast.inl"
}