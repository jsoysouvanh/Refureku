/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Refureku/Config.h>

//All this is NOT supported on MSVC compiler
#if RFK_TEMPLATE_TEMPLATE_SUPPORT

#include "TypeTemplateClassTemplate.h"

#include "Generated/TemplateTemplateClassTemplate.rfkh.h"

template <template <typename A> typename T>
class CLASS() SingleTemplateTemplateClassTemplate
{
	SingleTemplateTemplateClassTemplate_T_GENERATED
};

template <template <typename A, typename B, typename C> typename T, template <typename A> typename U>
class CLASS() MultipleTemplateTemplateClassTemplate
{
	MultipleTemplateTemplateClassTemplate_T_U_GENERATED
};

File_TemplateTemplateClassTemplate_GENERATED

#endif