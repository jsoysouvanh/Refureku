#include "Refureku/TypeInfo/Entity/EntityCast.h"

#include "Refureku/TypeInfo/Entity/EntityCastInternal.h"
#include "Refureku/TypeInfo/Variables/VariableAPI.h"
#include "Refureku/TypeInfo/Variables/FieldAPI.h"
#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"
#include "Refureku/TypeInfo/Functions/FunctionAPI.h"
#include "Refureku/TypeInfo/Functions/MethodAPI.h"
#include "Refureku/TypeInfo/Functions/StaticMethodAPI.h"
#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"
#include "Refureku/TypeInfo/Namespace/Namespace.h"

using namespace rfk;

template <>
Archetype const* rfk::entityCast<Archetype>(Entity const* entity) noexcept
{
	EEntityKind kind = entity->getKind();

	return (entity != nullptr &&
			(kind == EEntityKind::FundamentalArchetype || kind == EEntityKind::Struct || kind == EEntityKind::Class || kind == EEntityKind::Enum)) ?
		reinterpret_cast<Archetype const*>(entity) : nullptr;
}

template <>
FundamentalArchetype const* rfk::entityCast<FundamentalArchetype>(Entity const* entity) noexcept
{
	return internal::entityCast<FundamentalArchetype, EEntityKind::FundamentalArchetype>(entity);
}

template <>
StructAPI const* rfk::entityCast<StructAPI>(Entity const* entity) noexcept
{
	if (entity != nullptr)
	{
		EEntityKind kind = entity->getKind();

		return (kind == EEntityKind::Struct || kind == EEntityKind::Class) ? reinterpret_cast<StructAPI const*>(entity) : nullptr;
	}
	else
	{
		return nullptr;
	}
}

template <>
FieldBaseAPI const* rfk::entityCast<FieldBaseAPI>(Entity const* entity) noexcept
{
	return internal::entityCast<FieldBaseAPI, EEntityKind::Field>(entity);
}

template <>
FieldAPI const* rfk::entityCast<FieldAPI>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && !reinterpret_cast<FieldBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<FieldAPI const*>(entity) : nullptr;
}

template <>
StaticFieldAPI const* rfk::entityCast<StaticFieldAPI>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && reinterpret_cast<FieldBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<StaticFieldAPI const*>(entity) : nullptr;
}

template <>
MethodBaseAPI const* rfk::entityCast<MethodBaseAPI>(Entity const* entity) noexcept
{
	return internal::entityCast<MethodBaseAPI, EEntityKind::Method>(entity);
}

template <>
MethodAPI const* rfk::entityCast<MethodAPI>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && !reinterpret_cast<MethodBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<MethodAPI const*>(entity) : nullptr;
}

template <>
StaticMethodAPI const* rfk::entityCast<StaticMethodAPI>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && reinterpret_cast<MethodBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<StaticMethodAPI const*>(entity) : nullptr;
}

template <>
Enum const* rfk::entityCast<Enum>(Entity const* entity) noexcept
{
	return internal::entityCast<Enum, EEntityKind::Enum>(entity);
}

template <>
EnumValue const* rfk::entityCast<EnumValue>(Entity const* entity) noexcept
{
	return internal::entityCast<EnumValue, EEntityKind::EnumValue>(entity);
}

template <>
Namespace const* rfk::entityCast<Namespace>(Entity const* entity) noexcept
{
	return internal::entityCast<Namespace, EEntityKind::Namespace>(entity);
}

template <>
VariableAPI const* rfk::entityCast<VariableAPI>(Entity const* entity) noexcept
{
	return internal::entityCast<VariableAPI, EEntityKind::Variable>(entity);
}

template <>
FunctionAPI const* rfk::entityCast<FunctionAPI>(Entity const* entity) noexcept
{
	return internal::entityCast<FunctionAPI, EEntityKind::Function>(entity);
}