/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/Misc/TypeTraits.h"
#include "Refureku/Exceptions/InvalidArchetype.h"

namespace rfk::internal
{
	template <typename T>
	constexpr bool IsAdjustableInstanceValue = internal::isCallable_static_staticGetArchetype<T, Struct const&()>::value &&
												internal::isCallable_getArchetype<T, Struct const&()>::value;

	template <typename T>
	using IsAdjustableInstance = std::enable_if_t<IsAdjustableInstanceValue<T>>;

	/**
	*	@brief	Adjust the pointer address of the provided instance to another archetype.
	*			The provided instance type must implement both the staticGetArchetype static method and override the virtual getArchetype method.
	* 
	*	@tparam InstanceType Static type of the provided instance. It must implement the staticGetArchetype static method and override the virtual getArchetype method.
	* 
	*	@param instance			Instance pointer to adjust.
	*	@param targetArchetype	Archetype the pointer should be adjusted to.
	* 
	*	@return A pointer to the adjusted instance.
	* 
	*	@exception InvalidArchetype if the instance could not be casted to targetArchetype.
	*/
	template <typename InstanceType, typename = IsAdjustableInstance<InstanceType>>
	RFK_NODISCARD static InstanceType*	adjustInstancePointerAddress(InstanceType*		instance,
																	 rfk::Struct const&	targetArchetype);

	#include "Refureku/TypeInfo/MethodFieldHelpers.inl"
}