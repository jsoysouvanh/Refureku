#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"

#include <cstring>	//std::memcpy

#include "Refureku/TypeInfo/Variables/VariableBaseImpl.h"
#include "Refureku/Exceptions/ConstViolation.h"

using namespace rfk;

VariableBaseAPI::VariableBaseAPI(VariableBaseImpl* implementation) noexcept:
	Entity(implementation)
{
}

VariableBaseAPI::VariableBaseAPI(VariableBaseAPI&&) noexcept = default;

VariableBaseAPI::~VariableBaseAPI() noexcept = default;

Type const& VariableBaseAPI::getType() const noexcept
{
	return reinterpret_cast<VariableBaseImpl const*>(getPimpl())->getType();
}

void VariableBaseAPI::set(void* target, void const* source, std::size_t dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't use VariableBase::set on a const variable.");
	}

	std::memcpy(target, source, dataSize);
}

void VariableBaseAPI::throwConstViolationException(char const* message)
{
	throw ConstViolation(message);
}