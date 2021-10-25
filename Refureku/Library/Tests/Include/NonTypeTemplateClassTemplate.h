/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestEnum.h"

#include "Generated/NonTypeTemplateClassTemplate.rfkh.h"

template <std::size_t Value>
class CLASS() SingleNonTypeTemplateClassTemplate
{
	private:
		FIELD()
		int intArray[Value];

	SingleNonTypeTemplateClassTemplate_Value_GENERATED
};

//On MSVC, we must define the base getArchetype method for this since the variadic version is not recognized correctly
#if defined(_MSC_VER) && !defined(__clang__)

namespace rfk
{
	template <template <TestEnumClass, std::size_t> typename T>
	rfk::Archetype const* getArchetype()
	{
		return nullptr;
	}
}

#endif

template <TestEnumClass EnumClass, std::size_t Size>
class CLASS() MultipleNonTypeTemplateClassTemplate
{
	MultipleNonTypeTemplateClassTemplate_EnumClass_Size_GENERATED
};

File_NonTypeTemplateClassTemplate_GENERATED