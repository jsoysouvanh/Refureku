/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline TemplateArgument::TemplateArgumentImpl::TemplateArgumentImpl(ETemplateParameterKind templateKind) noexcept:
	_templateKind{templateKind}
{
}

inline ETemplateParameterKind TemplateArgument::TemplateArgumentImpl::getKind() const noexcept
{
	return _templateKind;
}