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
	static_assert(internal::isCallable_static_staticGetArchetype<SourceClassType, Struct const&()>::value, "[Refureku] The instance to cast must implement the staticGetArchetype static method.");
	static_assert(internal::isCallable_getArchetype<SourceClassType, Struct const&()>::value, "[Refureku] The instance to cast must override the virtual getArchetype method.");

	Struct const* targetArchetype = static_cast<Struct const*>(getArchetype<TargetClassType>());

	return (targetArchetype != nullptr) ? dynamicCast<TargetClassType>(instance, SourceClassType::staticGetArchetype(), instance->getArchetype(), *targetArchetype) : nullptr;
}

template <typename TargetClassType>
TargetClassType* dynamicCast(typename CopyConstness<TargetClassType, void>::Type* instance,
							 Struct const& instanceStaticArchetype, Struct const& instanceDynamicArchetype, Struct const& targetArchetype) noexcept
{
	return reinterpret_cast<TargetClassType*>(internal::dynamicCast(instance, instanceStaticArchetype, instanceDynamicArchetype, targetArchetype));
}

template <typename TargetClassType>
TargetClassType* dynamicUpCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& instanceStaticArchetype, Struct const& targetArchetype) noexcept
{
	return reinterpret_cast<TargetClassType*>(internal::dynamicUpCast(instance, instanceStaticArchetype, targetArchetype));
}

template <typename TargetClassType>
TargetClassType* dynamicDownCast(typename CopyConstness<TargetClassType, void>::Type* instance, Struct const& instanceStaticArchetype, Struct const& targetArchetype) noexcept
{
	return reinterpret_cast<TargetClassType*>(internal::dynamicDownCast(instance, instanceStaticArchetype, targetArchetype));
}