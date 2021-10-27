#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererImpl.h"

using namespace rfk;

NamespaceFragmentRegisterer::NamespaceFragmentRegisterer(NamespaceFragment const& namespaceFragment) noexcept:
	_pimpl(new internal::NamespaceFragmentRegistererImpl(namespaceFragment))
{
}

NamespaceFragmentRegisterer::~NamespaceFragmentRegisterer() noexcept = default;