/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"
#include "Generated/TestNestedClassTemplates.rfkh.h"

RFK_DEFINE_GET_ARCHETYPE_TEMPLATE(typename, auto)
RFK_DEFINE_GET_ARCHETYPE_TEMPLATE(typename, typename, auto)
RFK_DEFINE_GET_ARCHETYPE_TEMPLATE(template <typename, auto> typename)

class CLASS() NonNestedNonTemplateClass
{
	private:
		template <typename T>
		class CLASS() Lvl1NestedTypeTemplateParamClass
		{
			NonNestedNonTemplateClass_Lvl1NestedTypeTemplateParamClass_GENERATED
		};

		template <typename T, int Value>
		class CLASS() Lvl1NestedTypeTemplateParamNonTypeTemplateParamClass
		{
			NonNestedNonTemplateClass_Lvl1NestedTypeTemplateParamNonTypeTemplateParamClass_GENERATED
		};

		template <template <typename, std::size_t> typename T>
		class CLASS() Lvl1NestedTemplateTemplateParamClass
		{
			NonNestedNonTemplateClass_Lvl1NestedTemplateTemplateParamClass_GENERATED
		};

		class CLASS() Lvl1NestedNonTemplatePrivateClass
		{
			private:
				template <typename A, typename C, int Value>
				class CLASS() Lvl2NestedTemplatePrivateClass
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePrivateClass_Lvl2NestedTemplatePrivateClass_GENERATED
				};

			public:
				template <typename A, typename C, std::size_t Value>
				class CLASS() Lvl2NestedTemplatePublicClass
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePrivateClass_Lvl2NestedTemplatePublicClass_GENERATED
				};

			NonNestedNonTemplateClass_Lvl1NestedNonTemplatePrivateClass_GENERATED
		};

	public:
		class CLASS() Lvl1NestedNonTemplatePublicClass
		{
			private:
				template <typename A, typename C, char Value>
				class CLASS() Lvl2NestedTemplatePrivateClass2
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePublicClass_Lvl2NestedTemplatePrivateClass2_GENERATED
				};

			public:
				template <typename A, typename C, bool Value>
				class CLASS() Lvl2NestedTemplatePublicClass2
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePublicClass_Lvl2NestedTemplatePublicClass2_GENERATED
				};

			NonNestedNonTemplateClass_Lvl1NestedNonTemplatePublicClass_GENERATED
		};

	NonNestedNonTemplateClass_GENERATED
};

File_TestNestedClassTemplates_GENERATED