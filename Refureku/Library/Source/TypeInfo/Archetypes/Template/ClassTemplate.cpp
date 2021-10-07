#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateImpl.h"

using namespace rfk;

ClassTemplate::ClassTemplate(char const* name, std::size_t id, bool isClass) noexcept:
	Struct(new ClassTemplateImpl(name, id, isClass))
{
}

ClassTemplate::~ClassTemplate() noexcept = default;

TemplateParameter const& ClassTemplate::getTemplateParameterAt(std::size_t index) const noexcept
{
	return *reinterpret_cast<ClassTemplateImpl const*>(getPimpl())->getTemplateParameters()[index];
}

std::size_t ClassTemplate::getTemplateParametersCount() const noexcept
{
	return reinterpret_cast<ClassTemplateImpl const*>(getPimpl())->getTemplateParameters().size();
}

std::size_t ClassTemplate::getTemplateInstantiationsCount() const noexcept
{
	return reinterpret_cast<ClassTemplateImpl const*>(getPimpl())->getTemplateInstantiations().size();
}

void ClassTemplate::addTemplateParameter(TemplateParameter const& param) noexcept
{
	reinterpret_cast<ClassTemplateImpl*>(getPimpl())->addTemplateParameter(param);
}