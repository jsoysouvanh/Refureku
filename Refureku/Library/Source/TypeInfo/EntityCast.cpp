#include "Refureku/TypeInfo/EntityCast.h"

using namespace rfk;

template <>
Archetype const* rfk::entityCast<Archetype, void>(Entity const* entity) noexcept
{
	return (entity != nullptr &&
			(entity->kind == Entity::EKind::FundamentalArchetype || entity->kind == Entity::EKind::Struct || entity->kind == Entity::EKind::Class || entity->kind == Entity::EKind::Enum)) ?
			reinterpret_cast<Archetype const*>(entity) : nullptr;
}

template <>
FundamentalArchetype const* rfk::entityCast<FundamentalArchetype, void>(Entity const* entity) noexcept
{
	return internal::entityCast<FundamentalArchetype, Entity::EKind::FundamentalArchetype>(entity);
}

template <>
Struct const* rfk::entityCast<Struct, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && (entity->kind == Entity::EKind::Struct || entity->kind == Entity::EKind::Class)) ? reinterpret_cast<Struct const*>(entity) : nullptr;
}

template <>
Class const* rfk::entityCast<Class, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Class, Entity::EKind::Class>(entity);
}

template <>
FieldBase const* rfk::entityCast<FieldBase, void>(Entity const* entity) noexcept
{
	return internal::entityCast<FieldBase, Entity::EKind::Field>(entity);
}

template <>
Field const* rfk::entityCast<Field, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->kind == Entity::EKind::Field && !reinterpret_cast<FieldBase const*>(entity)->isStatic()) ? reinterpret_cast<Field const*>(entity) : nullptr;
}

template <>
StaticField const* rfk::entityCast<StaticField, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->kind == Entity::EKind::Field && reinterpret_cast<FieldBase const*>(entity)->isStatic()) ? reinterpret_cast<StaticField const*>(entity) : nullptr;
}

template <>
MethodBase const* rfk::entityCast<MethodBase, void>(Entity const* entity) noexcept
{
	return internal::entityCast<MethodBase, Entity::EKind::Method>(entity);
}

template <>
Method const* rfk::entityCast<Method, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->kind == Entity::EKind::Method && !reinterpret_cast<MethodBase const*>(entity)->isStatic()) ? reinterpret_cast<Method const*>(entity) : nullptr;
}

template <>
StaticMethod const* rfk::entityCast<StaticMethod, void>(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->kind == Entity::EKind::Method && reinterpret_cast<MethodBase const*>(entity)->isStatic()) ? reinterpret_cast<StaticMethod const*>(entity) : nullptr;
}

template <>
Enum const* rfk::entityCast<Enum, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Enum, Entity::EKind::Enum>(entity);
}

template <>
EnumValue const* rfk::entityCast<EnumValue, void>(Entity const* entity) noexcept
{
	return internal::entityCast<EnumValue, Entity::EKind::EnumValue>(entity);
}

template <>
Namespace const* rfk::entityCast<Namespace, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Namespace, Entity::EKind::Namespace>(entity);
}

template <>
Variable const* rfk::entityCast<Variable, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Variable, Entity::EKind::Variable>(entity);
}

template <>
Function const* rfk::entityCast<Function, void>(Entity const* entity) noexcept
{
	return internal::entityCast<Function, Entity::EKind::Function>(entity);
}