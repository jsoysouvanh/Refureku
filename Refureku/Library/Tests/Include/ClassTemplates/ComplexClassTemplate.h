#pragma once

#include "Generated/ComplexClassTemplate.rfkh.h"

enum class RFKEnum() ETemplateTestEnum
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

template <typename T, typename U, typename V>
class RFKClass() TypeTemplateClass
{
	TypeTemplateClass_T_U_V_GENERATED
};

template <int Value, char Char, ETemplateTestEnum EnumValue>
class RFKClass() NonTypeTemplateClass
{
	NonTypeTemplateClass_Value_Char_EnumValue_GENERATED
};

//template <template <typename A, typename B> typename TTParam, template <typename C, typename D> typename TTParam2>
//class RFKClass() TemplateTemplateClass
//{
//	TemplateTemplateClass_TTParam_TTParam2_GENERATED
//};

File_ComplexClassTemplate_GENERATED

template class RFKClass() TypeTemplateClass<int, float, double>;
template class RFKClass() NonTypeTemplateClass<4, 'a', ETemplateTestEnum::Value1>;
//template class RFKClass() TemplateTemplateClass<TypeTemplateClass, TypeTemplateClass>;