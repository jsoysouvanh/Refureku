#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameter.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.h"

using namespace rfk;

TemplateParameter::TemplateParameter(char const* name, ETemplateParameterKind kind) noexcept:
	_pimpl(new TemplateParameterImpl(name, kind))
{
}

TemplateParameter::~TemplateParameter() noexcept = default;