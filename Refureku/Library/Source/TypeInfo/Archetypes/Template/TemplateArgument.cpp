#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"

using namespace rfk;

TemplateArgument::TemplateArgument(TemplateArgumentImpl* implementation) noexcept:
	_pimpl(implementation)
{
}

TemplateArgument::~TemplateArgument() noexcept = default;

TemplateArgument::TemplateArgumentImpl* TemplateArgument::getPimpl() noexcept
{
	return _pimpl.get();
}

TemplateArgument::TemplateArgumentImpl const* TemplateArgument::getPimpl() const noexcept
{
	return _pimpl.get();
}

TemplateParameter const& TemplateArgument::getBoundParameter() const noexcept
{
	return _pimpl->getBoundParameter();
}