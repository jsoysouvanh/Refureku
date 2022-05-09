/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline TypeTemplateArgument::TypeTemplateArgumentImpl::TypeTemplateArgumentImpl(Type const& type) noexcept:
	TemplateArgumentImpl(ETemplateParameterKind::TypeTemplateParameter),
	_type{type}
{
}

inline Type const& TypeTemplateArgument::TypeTemplateArgumentImpl::getType() const noexcept
{
	return _type;
}