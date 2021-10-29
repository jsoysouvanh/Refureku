#pragma once

#include "../../../Public/Refureku/Properties/ParseAllNested.h"

#include <type_traits>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Namespace/Namespace.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>
#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h>

rfk::EEntityKind kodgen::ParseAllNested::getTargetEntityKind() const noexcept { return targetEntityKind; }
static_assert(std::is_base_of_v<rfk::Property, kodgen::ParseAllNested>, "[Refureku] Can't attach rfk::PropertySettings property to kodgen::ParseAllNested as it doesn't inherit from rfk::Property.");
namespace rfk::generated { 
 static rfk::NamespaceFragment const& getNamespaceFragment_5603044350098704190u_5959650475308226396() noexcept {
static rfk::NamespaceFragment fragment("kodgen", 5603044350098704190u);
static bool initialized = false;
if (!initialized) {
initialized = true;
fragment.setNestedEntitiesCapacity(1u);
fragment.addNestedEntity(*rfk::getArchetype<kodgen::ParseAllNested>());
}
return fragment; }
static rfk::NamespaceFragmentRegisterer namespaceFragmentRegisterer_5603044350098704190u_5959650475308226396(rfk::generated::getNamespaceFragment_5603044350098704190u_5959650475308226396());
 }
rfk::Class const& kodgen::ParseAllNested::staticGetArchetype() noexcept {
static bool initialized = false;
static rfk::Class type("ParseAllNested", 1518429735798145968u, sizeof(ParseAllNested), 1);
if (!initialized) {
initialized = true;
type.setPropertiesCapacity(1);
static_assert((rfk::PropertySettings::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] rfk::PropertySettings can't be applied to a rfk::EEntityKind::Class");static rfk::PropertySettings property_1518429735798145968u_0{rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct};type.addProperty(property_1518429735798145968u_0);
type.setDirectParentsCapacity(1);
type.addDirectParent(rfk::getArchetype<rfk::Property>(), static_cast<rfk::EAccessSpecifier>(1));
ParseAllNested::_rfk_registerChildClass<ParseAllNested>(type);
static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<ParseAllNested>>(),new rfk::NonMemberFunction<rfk::SharedPtr<ParseAllNested>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<ParseAllNested>),rfk::EMethodFlags::Default, nullptr);
type.addSharedInstantiator(defaultSharedInstantiator);
}
return type; }

rfk::Class const& kodgen::ParseAllNested::getArchetype() const noexcept { return ParseAllNested::staticGetArchetype(); }

template <> rfk::Archetype const* rfk::getArchetype<kodgen::ParseAllNested>() noexcept { return &kodgen::ParseAllNested::staticGetArchetype(); }


