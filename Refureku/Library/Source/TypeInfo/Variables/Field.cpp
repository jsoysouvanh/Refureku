#include "Refureku/TypeInfo/Variables/Field.h"

#include "Refureku/TypeInfo/Variables/FieldImpl.h"

using namespace rfk;

Field::Field(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
				   Struct const* owner, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBase(new FieldImpl(name, id, type, flags, owner, memoryOffset, outerEntity))
{
}

Field::Field(Field&&) noexcept = default;

Field::~Field() noexcept = default;

void Field::setInternal(void* instance, void const* valuePtr, std::size_t valueSize) const
{
	FieldBase::set(getPtrInternal(instance), valuePtr, valueSize);
}

void* Field::getPtrInternal(void* instance) const
{
	if (getType().isConst())
	{
		throwConstViolationException("Can't get a non-const ptr from a const field.");
	}

	return reinterpret_cast<uint8_t*>(instance) + getPimpl()->getMemoryOffset();
}

void const* Field::getConstPtrInternal(void const* instance) const noexcept
{
	return reinterpret_cast<uint8_t const*>(instance) + getPimpl()->getMemoryOffset();
}