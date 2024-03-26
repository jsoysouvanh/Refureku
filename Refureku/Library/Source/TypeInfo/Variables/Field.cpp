#include "Refureku/TypeInfo/Variables/Field.h"

#include "Refureku/TypeInfo/Variables/FieldImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<Field const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<Field const*, rfk::Allocator<Field const*>>;

Field::Field(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, EFieldFlags flags,
				   Struct const* owner, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBase(new FieldImpl(name, id, canonicalTypeName, type, flags, owner, memoryOffset, outerEntity))
{
}

Field::Field(Field&&) noexcept = default;

Field::~Field() noexcept = default;

std::size_t	Field::getMemoryOffset() const noexcept
{
	return getPimpl()->getMemoryOffset();
}

void Field::setUnsafe(void* instance, void const* valuePtr, std::size_t valueSize) const
{
	FieldBase::set(getPtrUnsafe(instance), valuePtr, valueSize);
}

void* Field::getPtrUnsafe(void* instance) const
{
	if (getType().isConst())
	{
		throwConstViolationException("Can't get a non-const ptr from a const field.");
	}

	return reinterpret_cast<uint8_t*>(instance) + getMemoryOffset();
}

void const* Field::getConstPtrUnsafe(void const* instance) const noexcept
{
	return reinterpret_cast<uint8_t const*>(instance) + getMemoryOffset();
}