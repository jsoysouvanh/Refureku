#pragma once

#include "../../../Public/Refureku/Properties/Instantiator.h"

#include <type_traits>
#include <Refureku/TypeInfo/Variables/VariableAPI.h>
#include <Refureku/TypeInfo/Functions/FunctionAPI.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegistererAPI.h>
#include <Refureku/TypeInfo/Namespace/Namespace.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateParameterAPI.h>

rfk::EEntityKind Instantiator::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, Instantiator>, "[Refureku] Can't attach PropertySettings property to Instantiator as it doesn't inherit from rfk::Property.");
namespace rfk::generated { static rfk::ArchetypeRegistererAPI registerer_16201336964262475043u = Instantiator::staticGetArchetype(); }

rfk::ClassAPI const& Instantiator::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::ClassAPI type("Instantiator", 16201336964262475043u, sizeof(Instantiator), 1);
if (!initialized) {
initialized = true;
type.setDefaultInstantiator(&rfk::internal::defaultInstantiator<Instantiator>);
type.setPropertiesCapacity(1);
static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a rfk::EEntityKind::Class");static PropertySettings property_16201336964262475043u_PropertySettings_0{rfk::EEntityKind::Method};type.addProperty(&property_16201336964262475043u_PropertySettings_0);
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetypeAPI<rfk::Property>(), static_cast<rfk::EAccessSpecifier>(1));
Instantiator::_rfk_registerChildClass<Instantiator>(type);
}
return type; }

rfk::ClassAPI const& Instantiator::getArchetype() const noexcept { return Instantiator::staticGetArchetype(); }

template <> rfk::ArchetypeAPI const* rfk::getArchetypeAPI<Instantiator>() noexcept { return &Instantiator::staticGetArchetype(); }


