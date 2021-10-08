#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameter.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.h"

using namespace rfk;

TemplateParameter::TemplateParameter(TemplateParameterImpl* implementation) noexcept:
	_pimpl(implementation)
{
}

TemplateParameter::~TemplateParameter() noexcept = default;

TemplateParameter::TemplateParameterImpl* TemplateParameter::getPimpl() noexcept
{
	return _pimpl.get();
}

TemplateParameter::TemplateParameterImpl const* TemplateParameter::getPimpl() const noexcept
{
	return _pimpl.get();
}

char const* TemplateParameter::getName() const noexcept
{
	return _pimpl->getName().data();
}

ETemplateParameterKind TemplateParameter::getKind() const noexcept
{
	return _pimpl->getKind();
}