#pragma once

#include "../../../Public/Refureku/TypeInfo/Properties/PropertySettings.h"

#include <type_traits>
#include <Refureku/TypeInfo/Namespaces/Namespace.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>
#include <Refureku/TypeInfo/Archetypes/TemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>
rfk::EEntityKind PropertySettings::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, PropertySettings>, "[Refureku] Can't attach PropertySettings property to PropertySettings as it doesn't inherit from rfk::Property.");
namespace rfk::generated { static rfk::ArchetypeRegisterer registerer_2708994343965683583u = PropertySettings::staticGetArchetype(); }

rfk::Class const& PropertySettings::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("PropertySettings", 2708994343965683583u, sizeof(PropertySettings), true);
if (!initialized) {
initialized = true;
type.setDefaultInstantiator(&rfk::defaultInstantiator<PropertySettings>);
type.setPropertiesCapacity(1);
static_assert((PropertySettings::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] PropertySettings can't be applied to a rfk::EEntityKind::Class");static PropertySettings property_2708994343965683583u_PropertySettings_0{rfk::EEntityKind::Struct | rfk::EEntityKind::Class};type.addProperty(&property_2708994343965683583u_PropertySettings_0);
type.setDirectParentsCapacity(1);
type.addParent<rfk::Property>(static_cast<rfk::EAccessSpecifier>(1));
PropertySettings::_rfk_registerChildClass<PropertySettings>(type);
}
return type; }

rfk::Class const& PropertySettings::getArchetype() const noexcept { return PropertySettings::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<PropertySettings>() noexcept { return &PropertySettings::staticGetArchetype(); }


