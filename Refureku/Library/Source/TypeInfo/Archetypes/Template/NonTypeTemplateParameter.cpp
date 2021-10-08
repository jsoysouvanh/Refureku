#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h"

#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameterImpl.h"

using namespace rfk;

NonTypeTemplateParameter::NonTypeTemplateParameter(char const* name, Archetype const* archetype) noexcept:
	TemplateParameter(new NonTypeTemplateParameterImpl(name, archetype))
{
}

NonTypeTemplateParameter::~NonTypeTemplateParameter() noexcept = default;

Archetype const* NonTypeTemplateParameter::getArchetype() const noexcept
{
	return reinterpret_cast<NonTypeTemplateParameterImpl const*>(getPimpl())->getArchetype();
}