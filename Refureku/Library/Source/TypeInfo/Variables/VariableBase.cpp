#include "Refureku/TypeInfo/Variables/VariableBase.h"

using namespace rfk;

VariableBase::VariableBase(std::string&& name, uint64 id, EEntityKind newKind, Type const& type) noexcept:
	Entity(std::forward<std::string>(name), id, newKind),
	type{type}
{
}