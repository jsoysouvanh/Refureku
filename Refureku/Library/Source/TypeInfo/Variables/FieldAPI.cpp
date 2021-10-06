#include "Refureku/TypeInfo/Variables/FieldAPI.h"

#include "Refureku/TypeInfo/Variables/FieldImpl.h"

using namespace rfk;

FieldAPI::FieldAPI(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
				   StructAPI const* owner, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBaseAPI(new FieldImpl(name, id, type, flags, owner, memoryOffset, outerEntity))
{
}

FieldAPI::FieldAPI(FieldAPI&&) noexcept = default;

FieldAPI::~FieldAPI() noexcept = default;

void FieldAPI::set(void* instance, void const* valuePtr, std::size_t valueSize) const
{
	FieldBaseAPI::set(getPtr(instance), valuePtr, valueSize);
}

void* FieldAPI::getPtr(void* instance) const noexcept
{
	return reinterpret_cast<uint8_t*>(instance) + reinterpret_cast<FieldImpl const*>(getPimpl())->getMemoryOffset();
}

void const* FieldAPI::getConstPtr(void const* instance) const noexcept
{
	return reinterpret_cast<uint8_t const*>(instance) + reinterpret_cast<FieldImpl const*>(getPimpl())->getMemoryOffset();
}