#include "Refureku/TypeInfo/Variables/FieldBaseAPI.h"

#include <type_traits>

#include "Refureku/TypeInfo/Variables/FieldBaseImpl.h"

using namespace rfk;

using EFieldFlagsUnderlyingType = std::underlying_type_t<EFieldFlags>;

FieldBaseAPI::FieldBaseAPI(FieldBaseImpl* implementation) noexcept:
	VariableBaseAPI(implementation)
{
}

FieldBaseAPI::~FieldBaseAPI() noexcept = default;

EAccessSpecifier FieldBaseAPI::getAccess() const noexcept
{
	EFieldFlags flags = reinterpret_cast<FieldBaseImpl const*>(getPimpl())->getFlags();

	return	(static_cast<EFieldFlagsUnderlyingType>(flags & EFieldFlags::Public) != static_cast<EFieldFlagsUnderlyingType>(0)) ? EAccessSpecifier::Public :
			(static_cast<EFieldFlagsUnderlyingType>(flags & EFieldFlags::Protected) != static_cast<EFieldFlagsUnderlyingType>(0)) ? EAccessSpecifier::Protected :
			(static_cast<EFieldFlagsUnderlyingType>(flags & EFieldFlags::Private) != static_cast<EFieldFlagsUnderlyingType>(0)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}

bool FieldBaseAPI::isStatic() const noexcept
{
	return static_cast<EFieldFlagsUnderlyingType>(getFlags() & EFieldFlags::Static) != static_cast<EFieldFlagsUnderlyingType>(0);
}

bool FieldBaseAPI::isMutable() const noexcept
{
	return static_cast<EFieldFlagsUnderlyingType>(getFlags() & EFieldFlags::Mutable) != static_cast<EFieldFlagsUnderlyingType>(0);
}

EFieldFlags FieldBaseAPI::getFlags() const noexcept
{
	return reinterpret_cast<FieldBaseImpl const*>(getPimpl())->getFlags();
}

StructAPI const* FieldBaseAPI::getOwner() const noexcept
{
	return reinterpret_cast<FieldBaseImpl const*>(getPimpl())->getOwner();
}