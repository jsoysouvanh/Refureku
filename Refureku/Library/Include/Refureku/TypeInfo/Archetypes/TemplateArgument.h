/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	//Forward declaration
	struct TemplateParameter;
	class Archetype;

	struct TemplateArgument
	{
		/** Template parameter this argument is a value of. */
		TemplateParameter const&	parameter;

		/** Archetype used for a template argument. */
		Archetype const*			archetype = nullptr;

		TemplateArgument(TemplateParameter const&	parameter,
						 Archetype const*			archetype)	noexcept;
	};
}

//TODO: Add support for NonTypeTemplateArguments