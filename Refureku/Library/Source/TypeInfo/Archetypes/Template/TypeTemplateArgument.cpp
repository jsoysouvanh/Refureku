#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgumentImpl.h"

using namespace rfk;

TypeTemplateArgument::TypeTemplateArgument(TemplateParameter const&	boundParameter, Archetype const* archetype) noexcept:
	TemplateArgument(new TypeTemplateArgumentImpl(boundParameter, archetype))
{
}

TypeTemplateArgument::~TypeTemplateArgument() noexcept = default;

Archetype const* TypeTemplateArgument::getArchetype() const noexcept
{
	return getPimpl()->getArchetype();
}

bool TypeTemplateArgument::operator==(TypeTemplateArgument const& other) const noexcept
{
	return getArchetype() != nullptr && getArchetype() == other.getArchetype();
}

bool TypeTemplateArgument::operator!=(TypeTemplateArgument const& other) const noexcept
{
	return !(*this == other);
}