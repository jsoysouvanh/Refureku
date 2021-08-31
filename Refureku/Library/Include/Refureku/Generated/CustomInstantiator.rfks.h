#pragma once

#include "../TypeInfo/Properties/CustomInstantiator.h"

#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <type_traits>
rfk::ArchetypeRegisterer CustomInstantiator::_rfk_archetypeRegisterer = &staticGetArchetype(); 
rfk::Struct const& CustomInstantiator::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Struct type("CustomInstantiator", 291713889535622996u, sizeof(CustomInstantiator), false);
if (!initialized) {
initialized = true;
type.setDefaultInstantiator(&rfk::defaultInstantiator<CustomInstantiator>);
type.properties.reserve(1);
static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Struct) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a rfk::EEntityKind::Struct");static PropertySettings property_CustomInstantiator_PropertySettings_0_291713889535622996u{rfk::EEntityKind::Method};type.properties.emplace_back(&property_CustomInstantiator_PropertySettings_0_291713889535622996u);
type.directParents.reserve(1);
type.addToParents<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));
CustomInstantiator::_rfk_registerChildClass<CustomInstantiator>(type);
}
return type; }

rfk::Struct const& CustomInstantiator::getArchetype() const noexcept { return CustomInstantiator::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<CustomInstantiator>() noexcept { return &CustomInstantiator::staticGetArchetype(); }
rfk::EEntityKind CustomInstantiator::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, CustomInstantiator>, "[Refureku] Can't attach PropertySettings property to CustomInstantiator as it doesn't inherit from rfk::Property.");
