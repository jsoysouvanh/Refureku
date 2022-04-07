#pragma once

#include "../../../Public/Refureku/Properties/Instantiator.h"

#include <type_traits>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Namespace/Namespace.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h>

rfk::EEntityKind rfk::Instantiator::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, rfk::Instantiator>, "[Refureku] Can't attach rfk::PropertySettings property to rfk::Instantiator as it doesn't inherit from rfk::Property.");
namespace rfk::generated { 
 static rfk::NamespaceFragment const& getNamespaceFragment_6202377051882013391u_13909718342397644637() noexcept {
static rfk::NamespaceFragment fragment("rfk", 6202377051882013391u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<rfk::Instantiator>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer const namespaceFragmentRegisterer_6202377051882013391u_13909718342397644637(rfk::generated::getNamespaceFragment_6202377051882013391u_13909718342397644637());
 }
rfk::Class const& rfk::Instantiator::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("Instantiator", 11099498566387530766u, sizeof(Instantiator), 1);
if (!initialized) {
initialized = true;
type.setPropertiesCapacity(1);
static_assert((rfk::PropertySettings::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] rfk::PropertySettings can't be applied to a rfk::EEntityKind::Class");static rfk::PropertySettings property_11099498566387530766u_0{rfk::EEntityKind::Method};type.addProperty(property_11099498566387530766u_0);
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<rfk::Property>(), static_cast<rfk::EAccessSpecifier>(1));
Instantiator::_rfk_registerChildClass<Instantiator>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Instantiator>>(),new rfk::NonMemberFunction<rfk::SharedPtr<Instantiator>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Instantiator>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
static rfk::StaticMethod defaultUniqueInstantiator("", 0u, rfk::getType<rfk::UniquePtr<Instantiator>>(),new rfk::NonMemberFunction<rfk::UniquePtr<Instantiator>()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<Instantiator>),rfk::EMethodFlags::Default, nullptr);
type.addUniqueInstantiator(defaultUniqueInstantiator);
type.setMethodsCapacity(0u); type.setStaticMethodsCapacity(0u); 
}
return type; }

rfk::Class const& rfk::Instantiator::getArchetype() const noexcept { return Instantiator::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<rfk::Instantiator>() noexcept { return &rfk::Instantiator::staticGetArchetype(); }


