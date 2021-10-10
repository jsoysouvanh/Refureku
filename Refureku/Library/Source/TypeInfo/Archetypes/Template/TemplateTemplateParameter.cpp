#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameterImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

TemplateTemplateParameter::TemplateTemplateParameter(char const* name) noexcept:
	TemplateParameter(new TemplateTemplateParameterImpl(name))
{
}

TemplateTemplateParameter::~TemplateTemplateParameter() noexcept = default;

std::size_t TemplateTemplateParameter::getTemplateParametersCount() const noexcept
{
	return reinterpret_cast<TemplateTemplateParameterImpl const*>(getPimpl())->getTemplateParameters().size();
}

TemplateParameter const* TemplateTemplateParameter::getTemplateParameterAt(std::size_t index) const noexcept
{
	return reinterpret_cast<TemplateTemplateParameterImpl const*>(getPimpl())->getTemplateParameters()[index];
}

bool TemplateTemplateParameter::foreachTemplateParameter(Visitor<TemplateParameter> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<TemplateTemplateParameterImpl const*>(getPimpl())->getTemplateParameters(), visitor, userData);
}

void TemplateTemplateParameter::addTemplateParameter(TemplateParameter const& param) noexcept
{
	reinterpret_cast<TemplateTemplateParameterImpl*>(getPimpl())->addTemplateParameter(param);
}