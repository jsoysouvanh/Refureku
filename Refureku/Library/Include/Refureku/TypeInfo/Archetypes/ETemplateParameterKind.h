/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	/**
	*	@brief Defines the kind of a template parameter.
	*/
	enum class ETemplateParameterKind
	{
		NonTypeTemplateParameter,
		TypeTemplateParameter,
		TemplateTemplateParameter
	};
}