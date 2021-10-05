/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline ClassTemplateAPI::ClassTemplateImpl::ClassTemplateImpl(char const* name, std::size_t id, bool isClass) noexcept:
	StructImpl(name, id, 0u, isClass, EClassKind::Template)
{
}

inline void ClassTemplateAPI::ClassTemplateImpl::addTemplateInstantiation(ClassTemplateInstantiationAPI const& instantiation) noexcept
{
	_templateInstantiations.push_back(&instantiation);
}

inline void ClassTemplateAPI::ClassTemplateImpl::addTemplateParameter(TemplateParameterAPI const& param) noexcept
{
	_templateParameters.push_back(&param);
}

inline std::vector<TemplateParameterAPI const*> const& ClassTemplateAPI::ClassTemplateImpl::getTemplateParameters() const noexcept
{
	return _templateParameters;
}

inline std::vector<ClassTemplateInstantiationAPI const*> const& ClassTemplateAPI::ClassTemplateImpl::getTemplateInstantiations() const noexcept
{
	return _templateInstantiations;
}