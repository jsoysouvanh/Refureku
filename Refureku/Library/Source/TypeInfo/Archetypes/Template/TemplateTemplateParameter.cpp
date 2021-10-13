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
	return getPimpl()->getTemplateParameters().size();
}

TemplateParameter const* TemplateTemplateParameter::getTemplateParameterAt(std::size_t index) const noexcept
{
	return getPimpl()->getTemplateParameters()[index];
}

bool TemplateTemplateParameter::foreachTemplateParameter(Visitor<TemplateParameter> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(getPimpl()->getTemplateParameters(), visitor, userData);
}

void TemplateTemplateParameter::addTemplateParameter(TemplateParameter const& param) noexcept
{
	getPimpl()->addTemplateParameter(param);
}