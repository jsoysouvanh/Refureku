#include "TypeInfo/Namespaces/NamespaceFragment.h"

using namespace rfk;

NamespaceFragment::NamespaceFragment(std::string&& newName, uint64 newId) noexcept:
	Entity(std::forward<std::string>(newName), newId, Entity::EKind::NamespaceFragment)
{
}