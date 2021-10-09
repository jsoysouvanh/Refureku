#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgumentImpl.h"

using namespace rfk;

TemplateTemplateArgument::TemplateTemplateArgument(TemplateParameter const& boundParameter, ClassTemplate const* value) noexcept:
	TemplateArgument(new TemplateTemplateArgumentImpl(boundParameter, value))
{
}

TemplateTemplateArgument::~TemplateTemplateArgument() noexcept = default;

ClassTemplate const* TemplateTemplateArgument::getValue() const noexcept
{
	return reinterpret_cast<TemplateTemplateArgumentImpl const*>(getPimpl())->getValue();
}