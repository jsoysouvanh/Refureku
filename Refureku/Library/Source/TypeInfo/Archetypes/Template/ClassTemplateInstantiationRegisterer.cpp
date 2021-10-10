#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegisterer.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererImpl.h"

using namespace rfk;

ClassTemplateInstantiationRegisterer::ClassTemplateInstantiationRegisterer(ClassTemplateInstantiation const& instantiation) noexcept:
	_pimpl(new internal::ClassTemplateInstantiationRegistererImpl(instantiation))
{
}

ClassTemplateInstantiationRegisterer::~ClassTemplateInstantiationRegisterer() noexcept = default;