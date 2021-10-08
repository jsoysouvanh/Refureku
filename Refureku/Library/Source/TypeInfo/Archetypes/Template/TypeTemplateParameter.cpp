#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h"

#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameterImpl.h"

using namespace rfk;

TypeTemplateParameter::TypeTemplateParameter(char const* name) noexcept:
	TemplateParameter(new TypeTemplateParameterImpl(name))
{
}

TypeTemplateParameter::~TypeTemplateParameter() noexcept = default;