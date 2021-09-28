/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
void TypeAPI::fillType(TypeAPI& out_type) noexcept
{
	TypePartAPI& currPart = out_type.addTypePart();

	//Const
	if constexpr (std::is_const_v<T>)
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::Const);
	}

	//Volatile
	if constexpr (std::is_volatile_v<T>)
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::Volatile);
	}

	if constexpr (std::is_array_v<T>)
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::CArray);
		currPart.setAdditionalData(static_cast<TypePartAPI::AdditionalDataType>(std::extent_v<T>));

		fillType<std::remove_extent_t<T>>(out_type);
	}
	else if constexpr (std::is_pointer_v<T>)
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::Ptr);
		fillType<std::remove_pointer_t<T>>(out_type);
	}
	else if constexpr (std::is_lvalue_reference_v<T>)
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::LRef);
		fillType<std::remove_reference_t<T>>(out_type);
	}
	else if constexpr (std::is_rvalue_reference_v<T>)
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::RRef);
		fillType<std::remove_reference_t<T>>(out_type);
	}
	else
	{
		currPart.addDescriptorFlag(ETypePartDescriptor::Value);

		out_type.setArchetype(rfk::getArchetypeAPI<std::decay_t<T>>());
	}
}

template <typename T>
TypeAPI const& getTypeAPI() noexcept
{
	static TypeAPI	result;
	static bool		initialized = false;

	if (!initialized)
	{
		initialized = true;

		TypeAPI::fillType<T>(result);
		result.optimizeMemory();
	}

	return result;
}