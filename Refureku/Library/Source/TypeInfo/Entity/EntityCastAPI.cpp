#include "Refureku/TypeInfo/Entity/EntityCastAPI.h"

#include "Refureku/TypeInfo/Variables/VariableAPI.h"
#include "Refureku/TypeInfo/Variables/FieldAPI.h"
#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"
#include "Refureku/TypeInfo/Functions/FunctionAPI.h"
#include "Refureku/TypeInfo/Functions/MethodAPI.h"
#include "Refureku/TypeInfo/Functions/StaticMethodAPI.h"
#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"
#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"
//#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeAPI.h"
#include "Refureku/TypeInfo/Namespace/NamespaceAPI.h"

using namespace rfk;

template <>
ArchetypeAPI const* rfk::entityCast<ArchetypeAPI, void>(EntityAPI const* entity) noexcept
{
	EEntityKind kind = entity->getKind();

	return (entity != nullptr &&
			(kind == EEntityKind::FundamentalArchetype || kind == EEntityKind::Struct || kind == EEntityKind::Class || kind == EEntityKind::Enum)) ?
		reinterpret_cast<ArchetypeAPI const*>(entity) : nullptr;
}

//TODO
//template <>
//FundamentalArchetype const* rfk::entityCast<FundamentalArchetype, void>(Entity const* entity) noexcept
//{
//	return internal::entityCast<FundamentalArchetype, EEntityKind::FundamentalArchetype>(entity);
//}

template <>
NamespaceAPI const* rfk::entityCast<NamespaceAPI, void>(EntityAPI const* entity) noexcept
{
	return internal::entityCast<NamespaceAPI, EEntityKind::Namespace>(entity);
}