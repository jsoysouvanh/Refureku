#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationImpl.h"
#include "Refureku/Misc/Algorithm.h"

using namespace rfk;

ClassTemplateInstantiation::ClassTemplateInstantiation(char const* name, std::size_t id, std::size_t memorySize, bool isClass, Archetype const& classTemplate) noexcept:
	Struct(new ClassTemplateInstantiationImpl(name, id, memorySize, isClass, classTemplate))
{
	//A getArchetype specialization should be generated for each template specialization, so instantiatedFrom should contain a ClassTemplate
	assert(classTemplate.getKind() == rfk::EEntityKind::Class || classTemplate.getKind() == rfk::EEntityKind::Struct);
	assert(static_cast<Class const&>(classTemplate).getClassKind() == EClassKind::Template);

	const_cast<ClassTemplate&>(getPimpl()->getClassTemplate()).registerTemplateInstantiation(*this);
}

ClassTemplateInstantiation::~ClassTemplateInstantiation() noexcept
{
	const_cast<ClassTemplate&>(getPimpl()->getClassTemplate()).unregisterTemplateInstantiation(*this);
}

ClassTemplate const& ClassTemplateInstantiation::getClassTemplate() const noexcept
{
	return getPimpl()->getClassTemplate();
}

TemplateArgument const& ClassTemplateInstantiation::getTemplateArgumentAt(std::size_t index) const noexcept
{
	return *getPimpl()->getTemplateArguments()[index];
}

bool ClassTemplateInstantiation::foreachTemplateArgument(Visitor<TemplateArgument> visitor, void* userData) const
{
	return Algorithm::foreach(getPimpl()->getTemplateArguments(), visitor, userData);
}

std::size_t ClassTemplateInstantiation::getTemplateArgumentsCount() const noexcept
{
	return getPimpl()->getTemplateArguments().size();
}

void ClassTemplateInstantiation::addTemplateArgument(TemplateArgument const& argument) noexcept
{
	getPimpl()->addTemplateArgument(argument);
}