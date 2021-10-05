#pragma once

#include "../../../Public/Refureku/Properties/PropertySettings.h"

#include <type_traits>
#include <Refureku/TypeInfo/Variables/VariableAPI.h>
#include <Refureku/TypeInfo/Functions/FunctionAPI.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegistererAPI.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegistererAPI.h>
#include <Refureku/TypeInfo/Namespace/NamespaceAPI.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentAPI.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererAPI.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateParameterAPI.h>

rfk::EEntityKind PropertySettings::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, PropertySettings>, "[Refureku] Can't attach PropertySettings property to PropertySettings as it doesn't inherit from rfk::Property.");
namespace rfk::generated { static rfk::ArchetypeRegistererAPI registerer_2708994343965683583u = PropertySettings::staticGetArchetype(); }

rfk::ClassAPI const& PropertySettings::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::ClassAPI type("PropertySettings", 2708994343965683583u, sizeof(PropertySettings), 1);
if (!initialized) {
initialized = true;
type.setDefaultInstantiator(&rfk::internal::defaultInstantiator<PropertySettings>);
type.setPropertiesCapacity(1);
static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a rfk::EEntityKind::Class");static PropertySettings property_2708994343965683583u_PropertySettings_0{rfk::EEntityKind::Struct | rfk::EEntityKind::Class};type.addProperty(&property_2708994343965683583u_PropertySettings_0);
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetypeAPI<rfk::Property>(), static_cast<rfk::EAccessSpecifier>(1));
PropertySettings::_rfk_registerChildClass<PropertySettings>(type);
}
return type; }

rfk::ClassAPI const& PropertySettings::getArchetype() const noexcept { return PropertySettings::staticGetArchetype(); }

template <> rfk::ArchetypeAPI const* rfk::getArchetypeAPI<PropertySettings>() noexcept { return &PropertySettings::staticGetArchetype(); }


