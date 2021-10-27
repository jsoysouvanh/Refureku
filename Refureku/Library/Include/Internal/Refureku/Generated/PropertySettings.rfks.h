#pragma once

#include "../../../Public/Refureku/Properties/PropertySettings.h"

#include <type_traits>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Namespace/Namespace.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h>

rfk::EEntityKind rfk::PropertySettings::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, rfk::PropertySettings>, "[Refureku] Can't attach rfk::PropertySettings property to rfk::PropertySettings as it doesn't inherit from rfk::Property.");
namespace rfk::generated { 
 static rfk::NamespaceFragment const& getNamespaceFragment_6202377051882013391u_15963945972659803745() noexcept {
static rfk::NamespaceFragment fragment("rfk", 6202377051882013391u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<rfk::PropertySettings>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer namespaceFragmentRegisterer_6202377051882013391u_15963945972659803745(rfk::generated::getNamespaceFragment_6202377051882013391u_15963945972659803745());
 }
rfk::Class const& rfk::PropertySettings::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("PropertySettings", 9343641787758265814u, sizeof(PropertySettings), 1);
if (!initialized) {
initialized = true;
type.setPropertiesCapacity(1);
static_assert((rfk::PropertySettings::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] rfk::PropertySettings can't be applied to a rfk::EEntityKind::Class");static rfk::PropertySettings property_9343641787758265814u_0{rfk::EEntityKind::Struct | rfk::EEntityKind::Class};type.addProperty(property_9343641787758265814u_0);
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<rfk::Property>(), static_cast<rfk::EAccessSpecifier>(1));
PropertySettings::_rfk_registerChildClass<PropertySettings>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<PropertySettings>>(),new rfk::NonMemberFunction<rfk::SharedPtr<PropertySettings>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<PropertySettings>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
}
return type; }

rfk::Class const& rfk::PropertySettings::getArchetype() const noexcept { return PropertySettings::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<rfk::PropertySettings>() noexcept { return &rfk::PropertySettings::staticGetArchetype(); }


