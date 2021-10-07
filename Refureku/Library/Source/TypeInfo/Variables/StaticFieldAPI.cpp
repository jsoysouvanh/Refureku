#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"

#include "Refureku/TypeInfo/Variables/StaticFieldImpl.h"

using namespace rfk;

StaticFieldAPI::StaticFieldAPI(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
							   StructAPI const* owner, void* ptr, Entity const* outerEntity) noexcept:
	FieldBaseAPI(new StaticFieldImpl(name, id, type, flags, owner, ptr, outerEntity))
{
}

StaticFieldAPI::StaticFieldAPI(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
							   StructAPI const* owner, void const* constPtr, Entity const* outerEntity) noexcept:
	FieldBaseAPI(new StaticFieldImpl(name, id, type, flags, owner, constPtr, outerEntity))
{
}

StaticFieldAPI::StaticFieldAPI(StaticFieldAPI&&) noexcept = default;

StaticFieldAPI::~StaticFieldAPI() noexcept = default;

void StaticFieldAPI::set(void const* valuePtr, std::size_t valueSize) const
{
	VariableBaseAPI::set(getPtr(), valuePtr, valueSize);
}

void* StaticFieldAPI::getPtr() const noexcept
{
	return reinterpret_cast<StaticFieldImpl const*>(getPimpl())->getPtr();
}

void const* StaticFieldAPI::getConstPtr() const noexcept
{
	return reinterpret_cast<StaticFieldImpl const*>(getPimpl())->getConstPtr();
}