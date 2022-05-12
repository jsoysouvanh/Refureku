/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename InstanceType, typename>
InstanceType* adjustInstancePointerAddress(InstanceType* instance, rfk::Struct const& targetArchetype)
{
	InstanceType* adjustedCallerPointer = rfk::dynamicCast<InstanceType>(instance, InstanceType::staticGetArchetype(), instance->getArchetype(), targetArchetype);

	if (adjustedCallerPointer != nullptr)
	{
		return adjustedCallerPointer;
	}
	else
	{
		throw InvalidArchetype("Failed to adjust the instance pointer since it has no relationship with the original class.");
	}
}