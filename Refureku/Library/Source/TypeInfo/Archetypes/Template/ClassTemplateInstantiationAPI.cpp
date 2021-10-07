#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationImpl.h"

using namespace rfk;

ClassTemplateInstantiationAPI::ClassTemplateInstantiationAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass, Archetype const& classTemplate) noexcept:
	Struct(new ClassTemplateInstantiationImpl(name, id, memorySize, isClass, classTemplate, *this))
{
}

ClassTemplateInstantiationAPI::~ClassTemplateInstantiationAPI() noexcept = default;


ClassTemplateAPI const& ClassTemplateInstantiationAPI::getClassTemplate() const noexcept
{
	return reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getClassTemplate();
}

TemplateArgumentAPI const& ClassTemplateInstantiationAPI::getTemplateArgument(std::size_t index) const noexcept
{
	return reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getTemplateArguments()[index];
}

std::size_t ClassTemplateInstantiationAPI::getTemplateArgumentsCount() const noexcept
{
	return reinterpret_cast<ClassTemplateInstantiationImpl const*>(getPimpl())->getTemplateArguments().size();
}

void ClassTemplateInstantiationAPI::addTemplateArgument(TemplateParameterAPI const& /*parameter*/, Archetype const* /*archetype*/) noexcept
{
	//TODO
}