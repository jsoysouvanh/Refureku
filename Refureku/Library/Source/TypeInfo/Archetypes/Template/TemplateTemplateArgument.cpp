#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgumentImpl.h"

using namespace rfk;

TemplateTemplateArgument::TemplateTemplateArgument(TemplateParameter const& boundParameter, ClassTemplate const* value) noexcept:
	TemplateArgument(new TemplateTemplateArgumentImpl(boundParameter, value))
{
}

TemplateTemplateArgument::~TemplateTemplateArgument() noexcept = default;

ClassTemplate const* TemplateTemplateArgument::getClassTemplate() const noexcept
{
	return getPimpl()->getValue();
}

bool TemplateTemplateArgument::operator==(TemplateTemplateArgument const& other) const noexcept
{
	return getClassTemplate() != nullptr && getClassTemplate() == other.getClassTemplate();
}

bool TemplateTemplateArgument::operator!=(TemplateTemplateArgument const& other) const noexcept
{
	return !(*this == other);
}