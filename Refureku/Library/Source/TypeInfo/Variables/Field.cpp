#include "Refureku/TypeInfo/Variables/Field.h"

#include "Refureku/TypeInfo/Variables/FieldImpl.h"

using namespace rfk;

Field::Field(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
				   StructAPI const* owner, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBase(new FieldImpl(name, id, type, flags, owner, memoryOffset, outerEntity))
{
}

Field::Field(Field&&) noexcept = default;

Field::~Field() noexcept = default;

void Field::set(void* instance, void const* valuePtr, std::size_t valueSize) const
{
	FieldBase::set(getPtr(instance), valuePtr, valueSize);
}

void* Field::getPtr(void* instance) const noexcept
{
	return reinterpret_cast<uint8_t*>(instance) + reinterpret_cast<FieldImpl const*>(getPimpl())->getMemoryOffset();
}

void const* Field::getConstPtr(void const* instance) const noexcept
{
	return reinterpret_cast<uint8_t const*>(instance) + reinterpret_cast<FieldImpl const*>(getPimpl())->getMemoryOffset();
}