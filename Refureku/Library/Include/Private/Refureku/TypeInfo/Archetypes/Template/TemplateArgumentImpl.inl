/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline TemplateArgumentAPI::TemplateArgumentImpl::TemplateArgumentImpl(TemplateParameterAPI const& boundParameter) noexcept:
	_boundParameter{boundParameter}
{
}

inline TemplateParameterAPI const& TemplateArgumentAPI::TemplateArgumentImpl::getBoundParameter() const noexcept
{
	return _boundParameter;
}