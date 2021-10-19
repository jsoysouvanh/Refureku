/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TypeTemplateClassTemplate.h"

#include "Generated/MixedClassTemplate.rfkh.h"

//Mixed template params, so must declare base getArchetype
namespace rfk
{
	template <template <typename, std::size_t> typename>
	rfk::Archetype const* getArchetype()
	{
		return nullptr;
	}
}

//Typical template signature for an std::array
template <typename T, std::size_t Size>
class CLASS() MixedClassTemplate
{
	MixedClassTemplate_T_Size_GENERATED
};


//Mixed template params, so must declare base getArchetype
namespace rfk
{
	template <template <typename, std::size_t, template <typename> typename> typename>
	rfk::Archetype const* getArchetype()
	{
		return nullptr;
	}
}

template <typename T, std::size_t Size, template <typename> typename U>
class CLASS() MixedClassTemplate2
{
	MixedClassTemplate2_T_Size_U_GENERATED
};

File_MixedClassTemplate_GENERATED

template class CLASS() MixedClassTemplate<int, 1u>;
template class CLASS() MixedClassTemplate2<float, 2u, SingleTypeTemplateClassTemplate>;