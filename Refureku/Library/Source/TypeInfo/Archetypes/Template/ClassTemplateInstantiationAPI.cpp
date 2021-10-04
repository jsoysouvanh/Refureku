#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationImpl.h"

using namespace rfk;

ClassTemplateInstantiationAPI::ClassTemplateInstantiationAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass, ArchetypeAPI const& classTemplate) noexcept:
	StructAPI(new ClassTemplateInstantiationImpl(name, id, memorySize, isClass, classTemplate))
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

void ClassTemplateInstantiationAPI::addTemplateArgument(TemplateParameterAPI const& /*parameter*/, ArchetypeAPI const* /*archetype*/) noexcept
{
	//TODO
}