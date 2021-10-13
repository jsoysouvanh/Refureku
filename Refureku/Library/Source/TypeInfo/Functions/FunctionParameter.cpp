#include "Refureku/TypeInfo/Functions/FunctionParameter.h"

#include "Refureku/TypeInfo/Functions/FunctionParameterImpl.h"

using namespace rfk;

FunctionParameter::FunctionParameter(char const* name, std::size_t id, Type const& type, Entity const* outerEntity) noexcept:
	Entity(new FunctionParameterImpl(name, id, type, outerEntity))
{
}

FunctionParameter::FunctionParameter(FunctionParameter&&) noexcept = default;

FunctionParameter::~FunctionParameter() noexcept = default;

Type const& FunctionParameter::getType() const noexcept
{
	return getPimpl()->getType();
}