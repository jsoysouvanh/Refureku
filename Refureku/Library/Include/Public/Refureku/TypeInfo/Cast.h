/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits> //std::is_class_v, is_base_of_v
#include <cassert>

#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"
#include "Refureku/Misc/CopyConstness.h"
#include "Refureku/Misc/TypeTraits.h"	//isCallable_static_staticGetArchetype, isCallable_getArchetype

namespace rfk
{
	//Forward declaration
	class Struct;

	/**
	*	@brief	Adjust the provided pointer to another class pointer if possible.
	* 
	*	@tparam TargetClassType Type to cast to.
	*	@tparam SourceClassType Static type of the provided instance to cast.
	* 
	*	@param instance A pointer to the instance to cast.
	* 
	*	@return The pointer to instance as targetArchetype if successful, else nullptr.
	*/
	template <typename TargetClassType, typename SourceClassType>
	RFK_NODISCARD TargetClassType*	dynamicCast(SourceClassType* instance)																noexcept;

	/**
	*	@brief Adjust the pointer of the provided instance of a given static/dynamic type to a pointer to another type if possible.
	* 
	*	@tparam TargetClassType Type to cast to.
	* 
	*	@param instance					Pointer to the instance to cast.
	*	@param instanceStaticArchetype	The static archetype of instance (the result of rfk::getArchetype<decltype(instance)>() before it was casted to void).
	*	@param instanceDynamicArchetype	The dynamic archetype of instance (the result of instance->getArchetype(), overriden from rfk::Object).
	*	@param targetArchetype			The archetype of TargetClassType.
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

	namespace internal
	{
		/**
		*	@brief	Adjust the provided pointer to another class pointer if possible.
		* 
		*	@param instance					A pointer to the instance to cast.
		*	@param instanceStaticArchetype	Static archetype of the instance pointer before it was casted to void*.
		*	@param instanceDynamicArchetype	Dynamic archetype of the instance pointer before it was casted to void*.
		*	@param targetArchetype			Archetype of the result pointer.
		* 
		*	@return The pointer to instance as targetArchetype if successful, else nullptr.
		*/
		RFK_NODISCARD REFUREKU_API void*		dynamicCast(void*		  instance,
															Struct const& instanceStaticArchetype,
															Struct const& instanceDynamicArchetype,
															Struct const& targetArchetype)				noexcept;

		/**
		*	@brief	Adjust the provided pointer to another class pointer if possible.
		*			Overload for const pointers.
		* 
		*	@param instance					A pointer to the instance to cast.
		*	@param instanceStaticArchetype	Static archetype of the instance pointer before it was casted to void*.
		*	@param instanceDynamicArchetype	Dynamic archetype of the instance pointer before it was casted to void*.
		*	@param targetArchetype			Archetype of the result pointer.
		* 
		*	@return The pointer to instance as targetArchetype if successful, else nullptr.
		*/
		RFK_NODISCARD REFUREKU_API void const*	dynamicCast(void const*	  instance,
															Struct const& instanceStaticArchetype,
															Struct const& instanceDynamicArchetype,
															Struct const& targetArchetype)				noexcept;

		/**
		*	@brief	Adjust the provided pointer to a parent class pointer if possible.
		*			This method will return non-nullptr results only if targetArchetype is a reflected parent class of instanceStaticArchetype,
		*			or is the instanceStaticArchetype itself.
		* 
		*	@param instance					A pointer to the instance to cast.
		*	@param instanceStaticArchetype	Static archetype of the instance pointer before it was casted to void*.
		*	@param targetArchetype			Archetype of the result pointer.
		* 
		*	@return The pointer to instance as targetArchetype if successful, else nullptr.
		*/
		RFK_NODISCARD REFUREKU_API void*		dynamicUpCast(void*			instance,
															  Struct const& instanceStaticArchetype,
															  Struct const&	targetArchetype)			noexcept;

		/**
		*	@brief	Adjust the provided pointer to a parent class pointer if possible.
		*			This method will return non-nullptr results only if targetArchetype is a reflected parent class of instanceStaticArchetype,
		*			or is the instanceStaticArchetype itself.
		*			Overload for const pointers.
		* 
		*	@param instance					A pointer to the instance to cast.
		*	@param instanceStaticArchetype	Static archetype of the instance pointer before it was casted to void*.
		*	@param targetArchetype			Archetype of the result pointer.
		* 
		*	@return The pointer to instance as targetArchetype if successful, else nullptr.
		*/
		RFK_NODISCARD REFUREKU_API void const*	dynamicUpCast(void const*	instance,
															  Struct const& instanceStaticArchetype,
															  Struct const&	targetArchetype)			noexcept;

		/**
		*	@brief	Adjust the provided pointer to a child class pointer if possible.
		*			This method will return non-nullptr results only if targetArchetype is a reflected subclass of instanceStaticArchetype,
		*			or is the instanceStaticArchetype itself.
		* 
		*	@param instance					A pointer to the instance to cast.
		*	@param instanceStaticArchetype	Static archetype of the instance pointer before it was casted to void*.
		*	@param targetArchetype			Archetype of the result pointer.
		* 
		*	@return The pointer to instance as targetArchetype if successful, else nullptr.
		*/
		RFK_NODISCARD REFUREKU_API void*		dynamicDownCast(void*		  instance,
																Struct const& instanceStaticArchetype,
																Struct const& targetArchetype)			noexcept;

		/**
		*	@brief	Adjust the provided pointer to a child class pointer if possible.
		*			This method will return non-nullptr results only if targetArchetype is a reflected subclass of instanceStaticArchetype,
		*			or is the instanceStaticArchetype itself.
		*			Overload for const pointers.
		* 
		*	@param instance					A pointer to the instance to cast.
		*	@param instanceStaticArchetype	Static archetype of the instance pointer before it was casted to void*.
		*	@param targetArchetype			Archetype of the result pointer.
		* 
		*	@return The pointer to instance as targetArchetype if successful, else nullptr.
		*/
		RFK_NODISCARD REFUREKU_API void const*	dynamicDownCast(void const*	  instance,
																Struct const& instanceStaticArchetype,
																Struct const& targetArchetype)			noexcept;
	}

	#include "Refureku/TypeInfo/Cast.inl"
}