#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h"

#include <cstring> //std::memcmp

#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgumentImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

using namespace rfk;

NonTypeTemplateArgument::NonTypeTemplateArgument(Archetype const* valueArchetype, void const* valuePtr) noexcept:
	TemplateArgument(new NonTypeTemplateArgumentImpl(valueArchetype, valuePtr))
{
}

NonTypeTemplateArgument::~NonTypeTemplateArgument() noexcept = default;

Archetype const* NonTypeTemplateArgument::getArchetype() const noexcept
{
	return getPimpl()->getArchetype();
}

void const* NonTypeTemplateArgument::getValuePtr() const noexcept
{
	return getPimpl()->getValuePtr();
}

bool NonTypeTemplateArgument::operator==(NonTypeTemplateArgument const& other) const noexcept
{
	Archetype const* const valueArchetype = getPimpl()->getArchetype();

	return	valueArchetype != nullptr &&
			valueArchetype == other.getPimpl()->getArchetype() &&
			std::memcmp(getPimpl()->getValuePtr(), other.getPimpl()->getValuePtr(), valueArchetype->getMemorySize()) == 0;
}

bool NonTypeTemplateArgument::operator!=(NonTypeTemplateArgument const& other) const noexcept
{
	return !(*this == other);
}