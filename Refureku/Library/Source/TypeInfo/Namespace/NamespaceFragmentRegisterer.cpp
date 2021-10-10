#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererImpl.h"

using namespace rfk;

NamespaceFragmentRegisterer::NamespaceFragmentRegisterer(char const* name, std::size_t id, NamespaceFragment const& namespaceFragment, bool isFileLevelNamespace) noexcept:
	_pimpl(new internal::NamespaceFragmentRegistererImpl(name, id, namespaceFragment, isFileLevelNamespace))
{
}

NamespaceFragmentRegisterer::~NamespaceFragmentRegisterer() noexcept = default;

Namespace const* NamespaceFragmentRegisterer::getNamespaceInstance() const noexcept
{
	return _pimpl->getNamespaceInstance();
}