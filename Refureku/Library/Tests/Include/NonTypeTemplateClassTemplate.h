/**
*	Copyright (c) 2021-2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>
#include "TestEnum.h"
#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"

#include "Generated/NonTypeTemplateClassTemplate.rfkh.h"

template <std::size_t Value>
class CLASS() SingleNonTypeTemplateClassTemplate
{
	private:
		FIELD()
		int intArray[Value];

	SingleNonTypeTemplateClassTemplate_GENERATED
};

//On MSVC, we must define the base getArchetype method for this since the variadic version is not recognized correctly
#if !RFK_TEMPLATE_TEMPLATE_SUPPORT

RFK_DEFINE_GET_ARCHETYPE_TEMPLATE(TestEnumClass, std::size_t)

#endif

template <TestEnumClass EnumClass, std::size_t Size>
class CLASS() MultipleNonTypeTemplateClassTemplate
{
	MultipleNonTypeTemplateClassTemplate_GENERATED
};

File_NonTypeTemplateClassTemplate_GENERATED