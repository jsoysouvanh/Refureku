/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline TemplateTemplateParameter::TemplateTemplateParameterImpl::TemplateTemplateParameterImpl(char const* name) noexcept:
	TemplateParameterImpl(name, ETemplateParameterKind::TemplateTemplateParameter)
{
}

inline void TemplateTemplateParameter::TemplateTemplateParameterImpl::addTemplateParameter(TemplateParameter const& param) noexcept
{
	_templateParams.push_back(&param);
}

inline std::vector<TemplateParameter const*> const& TemplateTemplateParameter::TemplateTemplateParameterImpl::getTemplateParameters() const noexcept
{
	return _templateParams;
}