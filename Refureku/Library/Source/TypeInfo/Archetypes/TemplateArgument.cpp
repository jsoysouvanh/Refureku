#include "Refureku/TypeInfo/Archetypes/TemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Archetype.h"

using namespace rfk;

TemplateArgument::TemplateArgument(TemplateParameter const& boundParameter, Archetype const* archetype) noexcept:
	_boundParameter{boundParameter},
	_archetype{archetype}
{
}

TemplateParameter const& TemplateArgument::getBoundParameter() const noexcept
{
	return _boundParameter;
}

Archetype const* TemplateArgument::getArchetype() const noexcept
{
	return _archetype;
}