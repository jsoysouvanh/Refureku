#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererImpl.h"

using namespace rfk;

NamespaceFragmentRegisterer::NamespaceFragmentRegisterer(NamespaceFragment const& namespaceFragment, bool isFileLevelNamespace) noexcept:
	_pimpl(new internal::NamespaceFragmentRegistererImpl(namespaceFragment, isFileLevelNamespace))
{
}

NamespaceFragmentRegisterer::~NamespaceFragmentRegisterer() noexcept = default;

Namespace const* NamespaceFragmentRegisterer::getNamespaceInstance() const noexcept
{
	return _pimpl->getNamespaceInstance();
}