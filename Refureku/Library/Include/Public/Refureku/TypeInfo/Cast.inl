/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename TargetClassType, typename SourceClassType>
TargetClassType* dynamicCast(SourceClassType* instance) noexcept
{
	static_assert(std::is_class_v<SourceClassType> && std::is_class_v<TargetClassType>, "[Refureku] Can't use dynamicCast with non-class types.");
	static_assert(!std::is_base_of_v<TargetClassType, SourceClassType>, "[Refureku] Don't use dynamicCast to perform a simple upcast. Use implicit conversion or static_cast instead.");
	static_assert(!std::is_same_v<SourceClassType, TargetClassType>, "[Refureku] Don't use dynamicCast to cast to the source type itself.");
	static_assert(std::is_base_of_v<rfk::Object, SourceClassType>, "[Refureku] Can't use dynamicCast if instance doesn't inherit from rfk::Object.");
	static_assert(internal::implements_getArchetype<SourceClassType, Struct const&()>::value, "[Refureku] Can't use dynamicCast if instance doesn't implement the getArchetype method."
																							 " Inherit from rfk::Object for automatic implementation generation, or implement it manually.");

	/**
	*	dynamicCast requires TargetClassType to implement the staticGetArchetype method, so
	*	TargetClassType must be reflected by rfk generator system for this dynamicCast to work.
	*	By the assumptions we made beforehand, there are no real valid reason not to reflect TargetClassType with Refureku since:
	*		1. SourceClassType must inherit from rfk::Object (and therefore is likely reflected using Refureku)
	*		2. SourceClassType is a base class of TargetClassType (since we perform a downcast... for an upcast an implicit compile-time static_cast does the job)
	* 
	*	To generate comprehensible errors, we still check at compile-time that TargetClassType indeed implements staticGetArchetype:
	*/
	static_assert(internal::implements_staticGetArchetype<TargetClassType, Struct const&()>::value, "[Refureku] The target class must implement the staticGetArchetype method.");

	return dynamicCast<TargetClassType>(instance, SourceClassType::staticGetArchetype(), instance->getArchetype(), TargetClassType::staticGetArchetype());
}

template <typename TargetClassType>
TargetClassType* dynamicCast(typename CopyConstness<TargetClassType, void>::Type* instance,
										   Struct const& instanceStaticArchetype, Struct const& instanceDynamicArchetype, Struct const& targetArchetype) noexcept
{
	//TODO: Optimization if the concrete type has a single branch inheritance tree: don't perform this intermediate computation

	auto adjustedStaticToDynamicInstancePointer = dynamicDownCast<TargetClassType>(instance, instanceStaticArchetype, instanceDynamicArchetype);

	// --------------------------------------------------------------------

	//Try to upcast the concrete type of instance to TargetClassType
	return dynamicUpCast<TargetClassType>(adjustedStaticToDynamicInstancePointer, instanceDynamicArchetype, targetArchetype);
}

template <typename TargetClassType>
TargetClassType* dynamicUpCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype) noexcept
{
	//If both both source and target types have the same archetype or instance is nullptr, there's no offset to perform
	if (fromArchetype == toArchetype || instance == nullptr)
	{
		return reinterpret_cast<TargetClassType*>(instance);
	}

	std::ptrdiff_t pointerOffset;

	//Get the memory offset
	//instance != nullptr is check in 2nd because it is not likely to happen a lot
	if (toArchetype.getSubclassPointerOffset(fromArchetype, pointerOffset))
	{
		return reinterpret_cast<TargetClassType*>(reinterpret_cast<typename CopyConstness<TargetClassType, uint8>::Type*>(instance) + pointerOffset);
	}

	return nullptr;
}

template <typename TargetClassType>
TargetClassType* dynamicDownCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& fromArchetype, Struct const& toArchetype) noexcept
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