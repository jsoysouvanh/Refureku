#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgumentImpl.h"

using namespace rfk;

NonTypeTemplateArgument::NonTypeTemplateArgument(TemplateParameter const& boundParameter, void const* valuePtr) noexcept:
	TemplateArgument(new NonTypeTemplateArgumentImpl(boundParameter, valuePtr))
{

}

NonTypeTemplateArgument::~NonTypeTemplateArgument() noexcept = default;

void const* NonTypeTemplateArgument::getValuePtr() const noexcept
{
	return reinterpret_cast<NonTypeTemplateArgumentImpl const*>(getPimpl())->getValuePtr();
}