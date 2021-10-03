#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererAPI.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererImpl.h"

using namespace rfk;

NamespaceFragmentRegistererAPI::NamespaceFragmentRegistererAPI(char const* name, std::size_t id, NamespaceFragmentAPI const& namespaceFragment, bool isFileLevelNamespace) noexcept:
	_pimpl(new internal::NamespaceFragmentRegistererImpl(name, id, namespaceFragment, isFileLevelNamespace))
{
}

NamespaceFragmentRegistererAPI::~NamespaceFragmentRegistererAPI() noexcept = default;

NamespaceAPI const* NamespaceFragmentRegistererAPI::getNamespaceInstance() const noexcept
{
	return _pimpl->getNamespaceInstance();
}