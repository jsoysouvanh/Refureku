/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/TemplateParameter.h"

namespace rfk
{
	struct TemplateArgument
	{
		/** Template parameter this argument is a value of. */
		TemplateParameter const&	parameter;

		/** Archetype used for a template argument. */
		Archetype const*			archetype = nullptr;

		//TODO: Constructor + add template arguments from TemplateClass::staticGetArchetype
	};
}

//TODO: Add support for NonTypeTemplateArguments