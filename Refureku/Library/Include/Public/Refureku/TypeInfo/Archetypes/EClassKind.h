/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

namespace rfk
{
	/**
	*	@brief	Defines the kind of a rfk::Class or a rfk::Struct instance:
	*			- Standard: The rfk::Class can't be cast to any more concrete type.
	*			- Template: The rfk::Class can be safely cast to rfk::ClassTemplate.
	*			- TemplateInstantiation: The rfk::Class can be safely cast to rfk::ClassTemplateInstantiation.
	*/
	enum class EClassKind
	{
		Standard,
		Template,
		TemplateInstantiation
	};
}