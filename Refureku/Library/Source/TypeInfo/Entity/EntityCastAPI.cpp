#include "Refureku/TypeInfo/Entity/EntityCastAPI.h"

#include "Refureku/TypeInfo/Entity/EntityCastInternal.h"
#include "Refureku/TypeInfo/Variables/VariableAPI.h"
#include "Refureku/TypeInfo/Variables/FieldAPI.h"
#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"
#include "Refureku/TypeInfo/Functions/FunctionAPI.h"
#include "Refureku/TypeInfo/Functions/MethodAPI.h"
#include "Refureku/TypeInfo/Functions/StaticMethodAPI.h"
#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"
#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeAPI.h"
#include "Refureku/TypeInfo/Namespace/NamespaceAPI.h"

using namespace rfk;

template <>
ArchetypeAPI const* rfk::entityCast<ArchetypeAPI>(EntityAPI const* entity) noexcept
{
	EEntityKind kind = entity->getKind();

	return (entity != nullptr &&
			(kind == EEntityKind::FundamentalArchetype || kind == EEntityKind::Struct || kind == EEntityKind::Class || kind == EEntityKind::Enum)) ?
		reinterpret_cast<ArchetypeAPI const*>(entity) : nullptr;
}

template <>
FundamentalArchetypeAPI const* rfk::entityCast<FundamentalArchetypeAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<FundamentalArchetypeAPI, EEntityKind::FundamentalArchetype>(entity);
}

template <>
StructAPI const* rfk::entityCast<StructAPI>(EntityAPI const* entity) noexcept
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
FieldBaseAPI const* rfk::entityCast<FieldBaseAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<FieldBaseAPI, EEntityKind::Field>(entity);
}

template <>
FieldAPI const* rfk::entityCast<FieldAPI>(EntityAPI const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && !reinterpret_cast<FieldBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<FieldAPI const*>(entity) : nullptr;
}

template <>
StaticFieldAPI const* rfk::entityCast<StaticFieldAPI>(EntityAPI const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && reinterpret_cast<FieldBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<StaticFieldAPI const*>(entity) : nullptr;
}

template <>
MethodBaseAPI const* rfk::entityCast<MethodBaseAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<MethodBaseAPI, EEntityKind::Method>(entity);
}

template <>
MethodAPI const* rfk::entityCast<MethodAPI>(EntityAPI const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && !reinterpret_cast<MethodBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<MethodAPI const*>(entity) : nullptr;
}

template <>
StaticMethodAPI const* rfk::entityCast<StaticMethodAPI>(EntityAPI const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && reinterpret_cast<MethodBaseAPI const*>(entity)->isStatic()) ? reinterpret_cast<StaticMethodAPI const*>(entity) : nullptr;
}

template <>
EnumAPI const* rfk::entityCast<EnumAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<EnumAPI, EEntityKind::Enum>(entity);
}

template <>
EnumValueAPI const* rfk::entityCast<EnumValueAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<EnumValueAPI, EEntityKind::EnumValue>(entity);
}

template <>
NamespaceAPI const* rfk::entityCast<NamespaceAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<NamespaceAPI, EEntityKind::Namespace>(entity);
}

template <>
VariableAPI const* rfk::entityCast<VariableAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<VariableAPI, EEntityKind::Variable>(entity);
}

template <>
FunctionAPI const* rfk::entityCast<FunctionAPI>(EntityAPI const* entity) noexcept
{
	return entityCast<FunctionAPI, EEntityKind::Function>(entity);
}