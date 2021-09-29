#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"

#include "Refureku/TypeInfo/Variables/VariableBaseImpl.h"

using namespace rfk;

VariableBaseAPI::VariableBaseAPI(VariableBaseImpl* implementation) noexcept:
	EntityAPI(implementation)
{
}

VariableBaseAPI::~VariableBaseAPI() noexcept = default;

TypeAPI const& VariableBaseAPI::getType() const noexcept
{
	return reinterpret_cast<VariableBaseImpl const*>(getPimpl())->getType();
}