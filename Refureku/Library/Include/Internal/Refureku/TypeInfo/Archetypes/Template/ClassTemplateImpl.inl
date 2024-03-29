/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline ClassTemplate::ClassTemplateImpl::ClassTemplateImpl(char const* name, std::size_t id, bool isClass) noexcept:
	StructImpl(name, id, 0u, isClass, EClassKind::Template)
{
}

inline void ClassTemplate::ClassTemplateImpl::addTemplateInstantiation(ClassTemplateInstantiation const& instantiation) noexcept
{
	_templateInstantiations.insert(&instantiation);
}

inline void ClassTemplate::ClassTemplateImpl::removeTemplateInstantiation(ClassTemplateInstantiation const& instantiation) noexcept
{
	_templateInstantiations.erase(&instantiation);
}

inline void ClassTemplate::ClassTemplateImpl::addTemplateParameter(TemplateParameter const& param) noexcept
{
	_templateParameters.push_back(&param);
}

inline std::vector<TemplateParameter const*> const& ClassTemplate::ClassTemplateImpl::getTemplateParameters() const noexcept
{
	return _templateParameters;
}

inline std::unordered_set<ClassTemplateInstantiation const*> const& ClassTemplate::ClassTemplateImpl::getTemplateInstantiations() const noexcept
{
	return _templateInstantiations;
}