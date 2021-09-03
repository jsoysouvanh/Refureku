#include "Refureku/TypeInfo/Variables/Variable.h"

using namespace rfk;

Variable::Variable(std::string&& name, uint64 id, Type const& type, void* address, EVarFlags flags) noexcept:
	VariableBase(std::forward<std::string>(name), id, EEntityKind::Variable, type),
	_address{address},
	flags{flags}
{
}

Variable::Variable(std::string&& name, uint64 id, Type const& type, void const* address, EVarFlags flags) noexcept:
	VariableBase(std::forward<std::string>(name), id, EEntityKind::Variable, type),
	_constAddress{address},
	flags{flags}
{
}

bool Variable::isStatic() const noexcept
{
	return (flags & EVarFlags::Static) != EVarFlags::Default;
}