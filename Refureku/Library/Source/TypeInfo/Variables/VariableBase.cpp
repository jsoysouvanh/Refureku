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
	return reinterpret_cast<VariableBaseImpl const*>(getPimpl())->getType();
}

void VariableBase::set(void* target, void const* source, std::size_t dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't use VariableBase::set on a const variable.");
	}

	std::memcpy(target, source, dataSize);
}

void VariableBase::throwConstViolationException(char const* message)
{
	throw ConstViolation(message);
}