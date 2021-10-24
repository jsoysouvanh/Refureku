#include "Refureku/TypeInfo/Entity/EntityCast.h"

#include "Refureku/TypeInfo/Entity/EntityCastInternal.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"
#include "Refureku/TypeInfo/Namespace/Namespace.h"

using namespace rfk;

Archetype const* rfk::archetypeCast(Entity const* entity) noexcept
{
	if (entity != nullptr)
	{
		EEntityKind kind = entity->getKind();

		return (kind == EEntityKind::FundamentalArchetype || kind == EEntityKind::Struct || kind == EEntityKind::Class || kind == EEntityKind::Enum) ?
			reinterpret_cast<Archetype const*>(entity) : nullptr;
	}
	else
	{
		return nullptr;
	}
}

FundamentalArchetype const* rfk::fundamentalArchetypeCast(Entity const* entity) noexcept
{
	return internal::entityCast<FundamentalArchetype, EEntityKind::FundamentalArchetype>(entity);
}

Struct const* rfk::structCast(Entity const* entity) noexcept
{
	return internal::entityCast<Struct, EEntityKind::Struct>(entity);
}

StructTemplate const* rfk::structTemplateCast(Entity const* entity) noexcept
{
	if (entity != nullptr)
	{
		return (entity->getKind() == EEntityKind::Struct && reinterpret_cast<Struct const*>(entity)->getClassKind() == EClassKind::Template) ?
			reinterpret_cast<StructTemplate const*>(entity) :
			nullptr;
	}
	else
	{
		return nullptr;
	}
}

StructTemplateInstantiation const* rfk::structTemplateInstantiationCast(Entity const* entity) noexcept
{
	if (entity != nullptr)
	{
		return (entity->getKind() == EEntityKind::Struct && reinterpret_cast<Struct const*>(entity)->getClassKind() == EClassKind::TemplateInstantiation) ?
			reinterpret_cast<StructTemplateInstantiation const*>(entity) :
			nullptr;
	}
	else
	{
		return nullptr;
	}
}

Class const* rfk::classCast(Entity const* entity) noexcept
{
	return internal::entityCast<Class, EEntityKind::Class>(entity);
}

ClassTemplate const* rfk::classTemplateCast(Entity const* entity) noexcept
{
	if (entity != nullptr)
	{
		return (entity->getKind() == EEntityKind::Class && reinterpret_cast<Class const*>(entity)->getClassKind() == EClassKind::Template) ?
			reinterpret_cast<ClassTemplate const*>(entity) :
			nullptr;
	}
	else
	{
		return nullptr;
	}
}

ClassTemplateInstantiation const* rfk::classTemplateInstantiationCast(Entity const* entity) noexcept
{
	if (entity != nullptr)
	{
		return (entity->getKind() == EEntityKind::Class && reinterpret_cast<Class const*>(entity)->getClassKind() == EClassKind::TemplateInstantiation) ?
			reinterpret_cast<ClassTemplateInstantiation const*>(entity) :
			nullptr;
	}
	else
	{
		return nullptr;
	}
}

Field const* rfk::fieldCast(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && !reinterpret_cast<FieldBase const*>(entity)->isStatic()) ?
		reinterpret_cast<Field const*>(entity) :
		nullptr;
}

StaticField const* rfk::staticFieldCast(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Field && reinterpret_cast<FieldBase const*>(entity)->isStatic()) ?
		reinterpret_cast<StaticField const*>(entity) :
		nullptr;
}

Method const* rfk::methodCast(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && !reinterpret_cast<MethodBase const*>(entity)->isStatic()) ?
		reinterpret_cast<Method const*>(entity) :
		nullptr;
}

StaticMethod const* rfk::staticMethodCast(Entity const* entity) noexcept
{
	return (entity != nullptr && entity->getKind() == EEntityKind::Method && reinterpret_cast<MethodBase const*>(entity)->isStatic()) ?
		reinterpret_cast<StaticMethod const*>(entity) :
		nullptr;
}

Enum const* rfk::enumCast(Entity const* entity) noexcept
{
	return internal::entityCast<Enum, EEntityKind::Enum>(entity);
}

EnumValue const* rfk::enumValueCast(Entity const* entity) noexcept
{
	return internal::entityCast<EnumValue, EEntityKind::EnumValue>(entity);
}

Namespace const* rfk::namespaceCast(Entity const* entity) noexcept
{
	return internal::entityCast<Namespace, EEntityKind::Namespace>(entity);
}

Variable const* rfk::variableCast(Entity const* entity) noexcept
{
	return internal::entityCast<Variable, EEntityKind::Variable>(entity);
}

Function const* rfk::functionCast(Entity const* entity) noexcept
{
	return internal::entityCast<Function, EEntityKind::Function>(entity);
}
