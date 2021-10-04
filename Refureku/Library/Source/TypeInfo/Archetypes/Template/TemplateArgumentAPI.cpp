#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentAPI.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"

using namespace rfk;

TemplateArgumentAPI::TemplateArgumentAPI(TemplateParameterAPI const& boundParameter) noexcept:
	_pimpl(new TemplateArgumentImpl(boundParameter))
{
}

TemplateArgumentAPI::~TemplateArgumentAPI() noexcept = default;


TemplateParameterAPI const& TemplateArgumentAPI::getBoundParameter() const noexcept
{
	return _pimpl->getBoundParameter();
}

ArchetypeAPI const* TemplateArgumentAPI::getArchetype() const noexcept
{
	return nullptr;
}