#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterAPI.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.h"

using namespace rfk;

TemplateParameterAPI::TemplateParameterAPI(char const* name, ETemplateParameterKind kind) noexcept:
	_pimpl(new TemplateParameterImpl(name, kind))
{
}

TemplateParameterAPI::~TemplateParameterAPI() noexcept = default;