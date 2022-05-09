#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgumentImpl.h"

using namespace rfk;

TypeTemplateArgument::TypeTemplateArgument(Type const& type) noexcept:
	TemplateArgument(new TypeTemplateArgumentImpl(type))
{
}

TypeTemplateArgument::~TypeTemplateArgument() noexcept = default;

Type const& TypeTemplateArgument::getType() const noexcept
{
	return getPimpl()->getType();
}

bool TypeTemplateArgument::operator==(TypeTemplateArgument const& other) const noexcept
{
	return getPimpl()->getType() == other.getPimpl()->getType();
}

bool TypeTemplateArgument::operator!=(TypeTemplateArgument const& other) const noexcept
{
	return !(*this == other);
}