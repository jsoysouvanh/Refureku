/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline TemplateParameterAPI::TemplateParameterImpl::TemplateParameterImpl(char const* name, ETemplateParameterKind kind) noexcept:
	_name(name),
	_kind{kind}
{
}

inline std::string const& TemplateParameterAPI::TemplateParameterImpl::getName() const noexcept
{
	return _name;
}

inline ETemplateParameterKind TemplateParameterAPI::TemplateParameterImpl::getKind() const noexcept
{
	return _kind;
}