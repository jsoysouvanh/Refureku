#include "Refureku/TypeInfo/Variables/VariableBase.h"

#include <cstring>	//std::memcpy

#include "Refureku/TypeInfo/Variables/VariableBaseImpl.h"
#include "Refureku/Exceptions/ConstViolation.h"

using namespace rfk;

VariableBase::VariableBase(VariableBaseImpl* implementation) noexcept:
	Entity(implementation)
{
}

VariableBase::VariableBase(VariableBase&&) noexcept = default;

VariableBase::~VariableBase() noexcept = default;

Type const& VariableBase::getType() const noexcept
{
	return getPimpl()->getType();
}

char const* VariableBase::getCanonicalTypeName() const noexcept
{
	return getPimpl()->getCanonicalTypeName();
}

void VariableBase::set(void* target, void const* source, std::size_t dataSize) const
{
	assert(!getType().isConst());

	std::memcpy(target, source, dataSize);
}

void VariableBase::throwConstViolationException(char const* message)
{
	throw ConstViolation(message);
}