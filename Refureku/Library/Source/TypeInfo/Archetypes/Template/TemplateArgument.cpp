#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"

using namespace rfk;

TemplateArgument::TemplateArgument(TemplateParameter const& boundParameter) noexcept:
	_pimpl(new TemplateArgumentImpl(boundParameter))
{
}

TemplateArgument::~TemplateArgument() noexcept = default;


TemplateParameter const& TemplateArgument::getBoundParameter() const noexcept
{
	return _pimpl->getBoundParameter();
}

Archetype const* TemplateArgument::getArchetype() const noexcept
{
	return nullptr;
}