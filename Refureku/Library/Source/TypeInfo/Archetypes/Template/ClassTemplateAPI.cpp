#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateAPI.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateImpl.h"

using namespace rfk;

ClassTemplateAPI::ClassTemplateAPI(char const* name, std::size_t id, bool isClass) noexcept:
	Struct(new ClassTemplateImpl(name, id, isClass))
{
}

ClassTemplateAPI::~ClassTemplateAPI() noexcept = default;

TemplateParameterAPI const& ClassTemplateAPI::getTemplateParameterAt(std::size_t index) const noexcept
{
	return *reinterpret_cast<ClassTemplateImpl const*>(getPimpl())->getTemplateParameters()[index];
}

std::size_t ClassTemplateAPI::getTemplateParametersCount() const noexcept
{
	return reinterpret_cast<ClassTemplateImpl const*>(getPimpl())->getTemplateParameters().size();
}

std::size_t ClassTemplateAPI::getTemplateInstantiationsCount() const noexcept
{
	return reinterpret_cast<ClassTemplateImpl const*>(getPimpl())->getTemplateInstantiations().size();
}

void ClassTemplateAPI::addTemplateParameter(TemplateParameterAPI const& param) noexcept
{
	reinterpret_cast<ClassTemplateImpl*>(getPimpl())->addTemplateParameter(param);
}