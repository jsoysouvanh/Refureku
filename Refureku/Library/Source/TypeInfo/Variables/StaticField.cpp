#include "Refureku/TypeInfo/Variables/StaticField.h"

#include "Refureku/TypeInfo/Variables/StaticFieldImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<StaticField const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<StaticField const*, rfk::Allocator<StaticField const*>>;

StaticField::StaticField(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
							   Struct const* owner, void* ptr, Entity const* outerEntity) noexcept:
	FieldBase(new StaticFieldImpl(name, id, type, flags, owner, ptr, outerEntity))
{
}

StaticField::StaticField(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
							   Struct const* owner, void const* constPtr, Entity const* outerEntity) noexcept:
	FieldBase(new StaticFieldImpl(name, id, type, flags, owner, constPtr, outerEntity))
{
}

StaticField::StaticField(StaticField&&) noexcept = default;

StaticField::~StaticField() noexcept = default;

void StaticField::set(void const* valuePtr, std::size_t valueSize) const
{
	VariableBase::set(getPtr(), valuePtr, valueSize);
}

void* StaticField::getPtr() const
{
	if (getType().isConst())
	{
		throwConstViolationException("Can't get a non-const ptr from a const variable.");
	}

	return getPimpl()->getPtr();
}

void const* StaticField::getConstPtr() const noexcept
{
	return getPimpl()->getConstPtr();
}