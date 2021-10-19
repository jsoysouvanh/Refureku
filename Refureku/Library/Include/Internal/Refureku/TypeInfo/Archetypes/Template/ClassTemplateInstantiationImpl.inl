/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline ClassTemplateInstantiation::ClassTemplateInstantiationImpl::ClassTemplateInstantiationImpl(char const* name, std::size_t id, std::size_t memorySize,
																									 bool isClass, Archetype const& classTemplate) noexcept:
	StructImpl(name, id, memorySize, isClass, EClassKind::TemplateInstantiation),
	_classTemplate{static_cast<ClassTemplate const&>(classTemplate)}
{
}

inline void ClassTemplateInstantiation::ClassTemplateInstantiationImpl::addTemplateArgument(TemplateArgument const& arg) noexcept
{
	_templateArguments.push_back(&arg);
}

inline ClassTemplate const& ClassTemplateInstantiation::ClassTemplateInstantiationImpl::getClassTemplate() const noexcept
{
	return _classTemplate;
}

inline std::vector<TemplateArgument const*> const& ClassTemplateInstantiation::ClassTemplateInstantiationImpl::getTemplateArguments() const noexcept
{
	return _templateArguments;
}