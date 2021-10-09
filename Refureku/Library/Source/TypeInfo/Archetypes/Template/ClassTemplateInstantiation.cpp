#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

ClassTemplateInstantiation::ClassTemplateInstantiation(char const* name, std::size_t id, std::size_t memorySize, bool isClass, Archetype const& classTemplate) noexcept:
	Struct(new ClassTemplateInstantiationImpl(name, id, memorySize, isClass, classTemplate, *this))
{
}

ClassTemplateInstantiation::~ClassTemplateInstantiation() noexcept = default;


ClassTemplate const& ClassTemplateInstantiation::getClassTemplate() const noexcept
{
	return reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getClassTemplate();
}

TemplateArgument const& ClassTemplateInstantiation::getTemplateArgumentAt(std::size_t index) const noexcept
{
	return *reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getTemplateArguments()[index];
}

bool ClassTemplateInstantiation::foreachTemplateArgument(Visitor<TemplateArgument> visitor, void* userData) const noexcept
{
	return EntityUtility::foreachEntity(reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getTemplateArguments(),
										visitor,
										userData);
}

std::size_t ClassTemplateInstantiation::getTemplateArgumentsCount() const noexcept
{
	return reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getTemplateArguments().size();
}

void ClassTemplateInstantiation::addTemplateArgument(TemplateArgument const& argument) noexcept
{
	reinterpret_cast<ClassTemplateInstantiationImpl*>(getPimpl())->addTemplateArgument(argument);
}