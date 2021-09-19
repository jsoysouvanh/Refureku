#include "Refureku/TypeInfo/Variables/VariableBase.h"

using namespace rfk;

VariableBase::VariableBase(std::string&& name, uint64 id, EEntityKind newKind, Type const& type, Entity const* outerEntity) noexcept:
	Entity(std::forward<std::string>(name), id, newKind, outerEntity),
	type{type}
{
}