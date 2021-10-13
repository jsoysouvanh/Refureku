#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h"

#include <cstring> //std::memcmp

#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgumentImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

using namespace rfk;

NonTypeTemplateArgument::NonTypeTemplateArgument(TemplateParameter const& boundParameter, void const* valuePtr) noexcept:
	TemplateArgument(new NonTypeTemplateArgumentImpl(boundParameter, valuePtr))
{
}

NonTypeTemplateArgument::~NonTypeTemplateArgument() noexcept = default;

void const* NonTypeTemplateArgument::getValuePtr() const noexcept
{
	return getPimpl()->getValuePtr();
}

bool NonTypeTemplateArgument::operator==(NonTypeTemplateArgument const& other) const noexcept
{
	Archetype const* paramArchetype = static_cast<NonTypeTemplateParameter const&>(getBoundParameter()).getArchetype();

	return	paramArchetype != nullptr &&
			paramArchetype == static_cast<NonTypeTemplateParameter const&>(other.getBoundParameter()).getArchetype() &&
			std::memcmp(getValuePtr(), other.getValuePtr(), paramArchetype->getMemorySize()) == 0;
}

bool NonTypeTemplateArgument::operator!=(NonTypeTemplateArgument const& other) const noexcept
{
	return !(*this == other);
}