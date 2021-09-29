#include "Refureku/TypeInfo/Variables/FieldAPI.h"

#include <cstring>	//std::memcpy

#include "Refureku/TypeInfo/Variables/FieldImpl.h"

using namespace rfk;

FieldAPI::FieldAPI(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
				   StructAPI const* owner, std::size_t memoryOffset, EntityAPI const* outerEntity) noexcept:
	FieldBaseAPI(new FieldImpl(name, id, type, flags, owner, memoryOffset, outerEntity))
{
}

FieldAPI::~FieldAPI() noexcept = default;

void FieldAPI::setData(void* instance, void const* data, std::size_t dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call Field::setData on a const field.");
	}

	std::memcpy(getDataPtr(instance), data, dataSize);
}

void* FieldAPI::getDataPtr(void* instance) const noexcept
{
	return reinterpret_cast<uint8_t*>(instance) + reinterpret_cast<FieldImpl const*>(getPimpl())->getMemoryOffset();
}

void const* FieldAPI::getDataPtr(void const* instance) const noexcept
{
	return reinterpret_cast<uint8_t const*>(instance) + reinterpret_cast<FieldImpl const*>(getPimpl())->getMemoryOffset();
}