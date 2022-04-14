#include "Refureku/TypeInfo/Cast.h"

using namespace rfk;

void* internal::dynamicCast(void* instance, Struct const& instanceStaticArchetype,
				  Struct const& instanceDynamicArchetype, Struct const& targetArchetype) noexcept
{
	return const_cast<void*>(internal::dynamicCast(reinterpret_cast<void const*>(instance), instanceStaticArchetype, instanceDynamicArchetype, targetArchetype));
}

void const* internal::dynamicCast(void const* instance, Struct const& instanceStaticArchetype,
						Struct const& instanceDynamicArchetype, Struct const& targetArchetype) noexcept
{
	//TODO: Optimization if the concrete type has a single branch inheritance tree: don't perform this intermediate computation

	void const* adjustedStaticToDynamicInstancePointer = internal::dynamicDownCast(instance, instanceStaticArchetype, instanceDynamicArchetype);

	// --------------------------------------------------------------------

	//Try to upcast the concrete type of instance to TargetClassType
	return internal::dynamicUpCast(adjustedStaticToDynamicInstancePointer, instanceDynamicArchetype, targetArchetype);
}

void* internal::dynamicUpCast(void* instance, Struct const& instanceStaticArchetype, Struct const& targetArchetype) noexcept
{
	return const_cast<void*>(internal::dynamicUpCast(reinterpret_cast<void const*>(instance), instanceStaticArchetype, targetArchetype));
}

void const* internal::dynamicUpCast(void const* instance, Struct const& instanceStaticArchetype, Struct const& targetArchetype) noexcept
{
	//If both both source and target types have the same archetype or instance is nullptr, there's no offset to perform
	if (instance == nullptr || instanceStaticArchetype == targetArchetype)
	{
		return instance;
	}

	std::ptrdiff_t pointerOffset;

	//Get the memory offset
	//instance != nullptr is check in 2nd because it is not likely to happen a lot
	if (targetArchetype.getSubclassPointerOffset(instanceStaticArchetype, pointerOffset))
	{
		return reinterpret_cast<uint8 const*>(instance) + pointerOffset;
	}

	return nullptr;
}

void* internal::dynamicDownCast(void* instance, Struct const& instanceStaticArchetype, Struct const& targetArchetype) noexcept
{
	return const_cast<void*>(internal::dynamicDownCast(reinterpret_cast<void const*>(instance), instanceStaticArchetype, targetArchetype));
}

void const* internal::dynamicDownCast(void const* instance, Struct const& instanceStaticArchetype, Struct const& targetArchetype) noexcept
{
	//If both both source and target types have the same archetype, there's no offset to perform
	if (instance == nullptr || instanceStaticArchetype == targetArchetype)
	{
		return instance;
	}

	std::ptrdiff_t pointerOffset;

	//Get the memory offset
	//instance != nullptr is check in 2nd because it is not likely to happen a lot
	if (instanceStaticArchetype.getSubclassPointerOffset(targetArchetype, pointerOffset))
	{
		return reinterpret_cast<uint8 const*>(instance) - pointerOffset;
	}

	return nullptr;
}