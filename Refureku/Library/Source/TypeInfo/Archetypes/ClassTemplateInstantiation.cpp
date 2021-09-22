#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstantiation.h"

#include <cassert>

#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"

using namespace rfk;

ClassTemplateInstantiation::ClassTemplateInstantiation(std::string&& name, std::size_t id, std::size_t memorySize, bool isClass, Archetype const& instantiatedFrom) noexcept:
	Class(std::forward<std::string>(name), id, memorySize, isClass, EClassKind::TemplateInstantiation),
	_instantiatedFrom{static_cast<ClassTemplate const&>(instantiatedFrom)}
{
	//A getArchetype specialization should be generated for each template specialization, so instantiatedFrom should contain a ClassTemplate
	assert(instantiatedFrom.getKind() == rfk::EEntityKind::Class || instantiatedFrom.getKind() == rfk::EEntityKind::Struct);
	assert(static_cast<Class const&>(instantiatedFrom).getClassKind() == EClassKind::Template);

	const_cast<ClassTemplate&>(static_cast<ClassTemplate const&>(instantiatedFrom)).registerClassTemplateInstantiation(*this);
}

void ClassTemplateInstantiation::addTemplateArgument(TemplateParameter const& parameter, Archetype const* archetype) noexcept
{
	templateArguments.emplace_back(parameter, archetype);
}

ClassTemplate const& ClassTemplateInstantiation::getInstantiatedFrom() const noexcept
{
	return _instantiatedFrom;
}

TemplateArgument const& ClassTemplateInstantiation::getTemplateArgument(std::size_t argIndex) const
{
	return templateArguments.at(argIndex);
}

std::size_t ClassTemplateInstantiation::getTemplateArgumentsCount() const noexcept
{
	return templateArguments.size();
}