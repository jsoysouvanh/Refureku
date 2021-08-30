/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Utility/TypeTraitsMacros.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"

GENERATE_IMPLEMENTS_TEMPLATE1_METHOD_TRAITS(_rfk_registerChildClass);

namespace rfk
{
	class CodeGenerationHelpers
	{
		public:
			CodeGenerationHelpers()		= delete;
			~CodeGenerationHelpers()	= delete;

			/**
			*	@brief	Register a child class to a parent class if the parent class implements
			*			the templated method "_registerChildClass" and the child class is reflected.
			*/
			template <typename ParentClass, typename ChildClass>
			static constexpr void registerChildClass(rfk::Struct& childClass) noexcept;
	};

	#include "Refureku/Utility/CodeGenerationHelpers.inl"
}