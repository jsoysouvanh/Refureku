#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"

#include <cstring>	//std::memcpy

#include "Refureku/TypeInfo/Variables/StaticFieldImpl.h"

using namespace rfk;

StaticFieldAPI::StaticFieldAPI(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
							   StructAPI const* owner, void* dataPtr, EntityAPI const* outerEntity) noexcept:
	FieldBaseAPI(new StaticFieldImpl(name, id, type, flags, owner, dataPtr, outerEntity))
{
}

StaticFieldAPI::StaticFieldAPI(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
							   StructAPI const* owner, void const* constDataPtr, EntityAPI const* outerEntity) noexcept:
	FieldBaseAPI(new StaticFieldImpl(name, id, type, flags, owner, constDataPtr, outerEntity))
{
}

StaticFieldAPI::~StaticFieldAPI() noexcept = default;

void StaticFieldAPI::setData(void const* data, std::size_t dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't call StaticField::setData on a const static field.");
	}

	std::memcpy(getDataPtr(), data, dataSize);
}

void* StaticFieldAPI::getDataPtr() const noexcept
{
	return reinterpret_cast<StaticFieldImpl const*>(getPimpl())->getDataPtr();
}

void const* StaticFieldAPI::getConstDataPtr() const noexcept
{
	return reinterpret_cast<StaticFieldImpl const*>(getPimpl())->getConstDataPtr();
}