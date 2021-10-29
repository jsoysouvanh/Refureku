/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline TemplateTemplateArgument::TemplateTemplateArgumentImpl::TemplateTemplateArgumentImpl(ClassTemplate const* value) noexcept:
	TemplateArgumentImpl(ETemplateParameterKind::TemplateTemplateParameter),
	_value{value}
{
}

inline ClassTemplate const* TemplateTemplateArgument::TemplateTemplateArgumentImpl::getValue() const noexcept
{
	return _value;
}