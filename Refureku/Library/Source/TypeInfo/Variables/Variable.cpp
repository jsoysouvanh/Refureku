#include "Refureku/TypeInfo/Variables/Variable.h"

using namespace rfk;

Variable::Variable(std::string&& name, std::size_t id, Type const& type, void* address, EVarFlags flags) noexcept:
	VariableBase(std::forward<std::string>(name), id, EEntityKind::Variable, type),
	_flags{flags},
	_address{address}
{
}

Variable::Variable(std::string&& name, std::size_t id, Type const& type, void const* address, EVarFlags flags) noexcept:
	VariableBase(std::forward<std::string>(name), id, EEntityKind::Variable, type),
	_flags{flags},
	_constAddress{address}
{
}