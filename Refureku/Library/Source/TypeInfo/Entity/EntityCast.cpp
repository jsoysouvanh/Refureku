#include "Refureku/TypeInfo/Entity/EntityCast.h"

#include "Refureku/TypeInfo/Entity/EntityCastInternal.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"
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
FieldBase const* rfk::entityCast<FieldBase>(Entity const* entity) noexcept
{
	return internal::entityCast<FieldBase, EEntityKind::Field>(entity);
}

template <>
Field const* rfk::entityCast<Field>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && !reinterpret_cast<FieldBase const*>(entity)->isStatic()) ? reinterpret_cast<Field const*>(entity) : nullptr;
}

template <>
StaticField const* rfk::entityCast<StaticField>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && reinterpret_cast<FieldBase const*>(entity)->isStatic()) ? reinterpret_cast<StaticField const*>(entity) : nullptr;
}

template <>
MethodBase const* rfk::entityCast<MethodBase>(Entity const* entity) noexcept
{
	return internal::entityCast<MethodBase, EEntityKind::Method>(entity);
}

template <>
Method const* rfk::entityCast<Method>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && !reinterpret_cast<MethodBase const*>(entity)->isStatic()) ? reinterpret_cast<Method const*>(entity) : nullptr;
}

template <>
StaticMethod const* rfk::entityCast<StaticMethod>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && reinterpret_cast<MethodBase const*>(entity)->isStatic()) ? reinterpret_cast<StaticMethod const*>(entity) : nullptr;
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
Variable const* rfk::entityCast<Variable>(Entity const* entity) noexcept
{
	return internal::entityCast<Variable, EEntityKind::Variable>(entity);
}

template <>
Function const* rfk::entityCast<Function>(Entity const* entity) noexcept
{
	return internal::entityCast<Function, EEntityKind::Function>(entity);
}