#include "Refureku/TypeInfo/Archetypes/TemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Archetypes/TemplateParameter.h"

using namespace rfk;

TemplateArgument::TemplateArgument(TemplateParameter const& parameter, Archetype const* archetype) noexcept:
	parameter{parameter},
	archetype{archetype}
{
}