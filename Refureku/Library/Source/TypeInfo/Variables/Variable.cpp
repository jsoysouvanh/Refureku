#include "Refureku/TypeInfo/Variables/Variable.h"

#include "Refureku/TypeInfo/Variables/VariableImpl.h"
#include "Refureku/Exceptions/ConstViolation.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<Variable const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<Variable const*, rfk::Allocator<Variable const*>>;

Variable::Variable(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, void* ptr, EVarFlags flags) noexcept:
	VariableBase(new VariableImpl(name, id, canonicalTypeName, type, ptr, flags))
{
}

Variable::Variable(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, void const* constPtr, EVarFlags flags) noexcept:
	VariableBase(new VariableImpl(name, id, canonicalTypeName, type, constPtr, flags))
{
}

Variable::Variable(Variable&&) noexcept = default;

Variable::~Variable() noexcept = default;

bool Variable::isStatic() const noexcept
{
	using EVarFlagsUnderlyingType = std::underlying_type_t<EVarFlags>;

	return static_cast<EVarFlagsUnderlyingType>(getFlags() & EVarFlags::Static) != static_cast<EVarFlagsUnderlyingType>(0);
}

void Variable::set(void const* valuePtr, std::size_t valueSize) const
{
	VariableBase::set(getPtr(), valuePtr, valueSize);
}

EVarFlags Variable::getFlags() const noexcept
{
	return getPimpl()->getFlags();
}

void* Variable::getPtr() const
{
	if (getType().isConst())
	{
		throwConstViolationException("Can't get a non-const ptr from a const variable.");
	}

	return getPimpl()->getPtr();
}

void const* Variable::getConstPtr() const noexcept
{
	return getPimpl()->getConstPtr();
}