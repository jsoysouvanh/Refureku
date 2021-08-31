#pragma once

#include "..\TypeInfo\Properties\PropertySettings.h"

#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <type_traits>
rfk::ArchetypeRegisterer PropertySettings::_rfk_archetypeRegisterer = &staticGetArchetype(); 
rfk::Struct const& PropertySettings::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Struct type("PropertySettings", 2708994343965683583u, sizeof(PropertySettings), false);
if (!initialized) {
initialized = true;
type.setDefaultInstantiator(&rfk::defaultInstantiator<PropertySettings>);
type.properties.reserve(1);
static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Struct) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a rfk::EEntityKind::Struct");static PropertySettings property_PropertySettings_PropertySettings_0_2708994343965683583u{rfk::EEntityKind::Struct | rfk::EEntityKind::Class};type.properties.emplace_back(&property_PropertySettings_PropertySettings_0_2708994343965683583u);
type.directParents.reserve(1);
type.addToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));
PropertySettings::_rfk_registerChildClass<PropertySettings>(type);
}
return type; }

rfk::Struct const& PropertySettings::getArchetype() const noexcept { return PropertySettings::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<PropertySettings>() noexcept { return &PropertySettings::staticGetArchetype(); }
rfk::EEntityKind PropertySettings::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, PropertySettings>, "[Refureku] Can't attach PropertySettings property to PropertySettings as it doesn't inherit from rfk::Property.");
