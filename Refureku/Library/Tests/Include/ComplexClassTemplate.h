/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Generated/ComplexClassTemplate.rfkh.h"

enum class ENUM() ETemplateTestEnum
{
	Value1
};

namespace rfk
{
#if defined(_MSC_VER) && !defined(__clang__)
	template <template <int, char, ETemplateTestEnum> typename>
	Archetype const* getArchetype() noexcept
	{
		return nullptr;
	}
#endif
}

template <typename T, typename U>
class CLASS() TypeTemplateClass
{
	TypeTemplateClass_T_U_GENERATED
};

template <int Value, char Char, ETemplateTestEnum EnumValue>
class CLASS() NonTypeTemplateClass
{
	NonTypeTemplateClass_Value_Char_EnumValue_GENERATED
};

//template <template <typename A, typename B> typename TTParam, template <typename C, typename D> typename TTParam2>
//class RFKClass() TemplateTemplateClass
//{
//	TemplateTemplateClass_TTParam_TTParam2_GENERATED
//};

File_ComplexClassTemplate_GENERATED

template class CLASS() TypeTemplateClass<int, float>;
template class CLASS() NonTypeTemplateClass<4, 'a', ETemplateTestEnum::Value1>;
//template class RFKClass() TemplateTemplateClass<TypeTemplateClass, TypeTemplateClass>;