#include "Refureku/TypeInfo/Functions/FunctionParameterAPI.h"

#include "Refureku/TypeInfo/Functions/FunctionParameterImpl.h"

using namespace rfk;

FunctionParameterAPI::FunctionParameterAPI(char const* name, std::size_t id, TypeAPI const& type, Entity const* outerEntity) noexcept:
	Entity(new FunctionParameterImpl(name, id, type, outerEntity))
{
}

FunctionParameterAPI::FunctionParameterAPI(FunctionParameterAPI&&) noexcept = default;

FunctionParameterAPI::~FunctionParameterAPI() noexcept = default;

TypeAPI const& FunctionParameterAPI::getType() const noexcept
{
	return reinterpret_cast<FunctionParameterImpl const*>(getPimpl())->getType();
}