#include "Refureku/TypeInfo/Entity/EntityCast.h"

using namespace rfk;

template <>
Archetype const* rfk::entityCast<Archetype, void>(Entity const* entity) noexcept
{
	EEntityKind kind = entity->getKind();

	return (entity != nullptr &&
			(kind == EEntityKind::FundamentalArchetype || kind == EEntityKind::Struct || kind == EEntityKind::Class || kind == EEntityKind::Enum)) ?
			reinterpret_cast<Archetype const*>(entity) : nullptr;
}

template <>
FundamentalArchetype const* rfk::entityCast<FundamentalArchetype, void>(Entity const* entity) noexcept
{
	return internal::entityCast<FundamentalArchetype, EEntityKind::FundamentalArchetype>(entity);
}

template <>
Struct const* rfk::entityCast<Struct, void>(Entity const* entity) noexcept
{
	EEntityKind kind = entity->getKind();

	return (entity != nullptr && (kind == EEntityKind::Struct || kind == EEntityKind::Class)) ? reinterpret_cast<Struct const*>(entity) : nullptr;
}

template <>
FieldBase const* rfk::entityCast<FieldBase, void>(Entity const* entity) noexcept
{
	return internal::entityCast<FieldBase, EEntityKind::Field>(entity);
}

template <>
Field const* rfk::entityCast<Field, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && !reinterpret_cast<FieldBase const*>(entity)->isStatic()) ? reinterpret_cast<Field const*>(entity) : nullptr;
}

template <>
StaticField const* rfk::entityCast<StaticField, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && reinterpret_cast<FieldBase const*>(entity)->isStatic()) ? reinterpret_cast<StaticField const*>(entity) : nullptr;
}

template <>
MethodBase const* rfk::entityCast<MethodBase, void>(Entity const* entity) noexcept
{
	return internal::entityCast<MethodBase, EEntityKind::Method>(entity);
}

template <>
Method const* rfk::entityCast<Method, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && !reinterpret_cast<MethodBase const*>(entity)->isStatic()) ? reinterpret_cast<Method const*>(entity) : nullptr;
}

template <>
StaticMethod const* rfk::entityCast<StaticMethod, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && reinterpret_cast<MethodBase const*>(entity)->isStatic()) ? reinterpret_cast<StaticMethod const*>(entity) : nullptr;
}

template <>
Enum const* rfk::entityCast<Enum, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Enum, EEntityKind::Enum>(entity);
}

template <>
EnumValue const* rfk::entityCast<EnumValue, void>(Entity const* entity) noexcept
{
	return internal::entityCast<EnumValue, EEntityKind::EnumValue>(entity);
}

template <>
Namespace const* rfk::entityCast<Namespace, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Namespace, EEntityKind::Namespace>(entity);
}

template <>
Variable const* rfk::entityCast<Variable, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Variable, EEntityKind::Variable>(entity);
}

template <>
Function const* rfk::entityCast<Function, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Function, EEntityKind::Function>(entity);
}