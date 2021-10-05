#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererAPI.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererImpl.h"

using namespace rfk;

ClassTemplateInstantiationRegistererAPI::ClassTemplateInstantiationRegistererAPI(ClassTemplateInstantiationAPI const& instantiation) noexcept:
	_pimpl(new internal::ClassTemplateInstantiationRegistererImpl(instantiation))
{
}

ClassTemplateInstantiationRegistererAPI::~ClassTemplateInstantiationRegistererAPI() noexcept = default;