#pragma once

#include "../TypeInfo/Properties/PropertySettings.h"

#include <type_traits>
#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <Refureku/TypeInfo/Archetypes/TemplateParameter.h>
rfk::EEntityKind PropertySettings::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, PropertySettings>, "[Refureku] Can't attach PropertySettings property to PropertySettings as it doesn't inherit from rfk::Property.");
rfk::ArchetypeRegisterer rfk::generated::_rfk_archetypeRegisterer_2708994343965683583u = PropertySettings::staticGetArchetype(); 

rfk::Struct const& PropertySettings::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Struct type("PropertySettings", 2708994343965683583u, sizeof(PropertySettings), false);
if (!initialized) {
initialized = true;
type.setDefaultInstantiator(&rfk::defaultInstantiator<PropertySettings>);
type.properties.reserve(1);
static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Struct) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a rfk::EEntityKind::Struct");static PropertySettings property_2708994343965683583u_PropertySettings_0{rfk::EEntityKind::Struct | rfk::EEntityKind::Class};type.properties.emplace_back(&property_2708994343965683583u_PropertySettings_0);
type.directParents.reserve(1);
type.addToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));
PropertySettings::_rfk_registerChildClass<PropertySettings>(type);
}
return type; }

rfk::Struct const& PropertySettings::getArchetype() const noexcept { return PropertySettings::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<PropertySettings>() noexcept { return &PropertySettings::staticGetArchetype(); }


