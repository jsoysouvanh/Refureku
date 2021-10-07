#pragma once

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Entity/EEntityKind.h>
#include <string>
#include <Refureku/Utility/CodeGenerationHelpers.h>
#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/TypeInfo/Functions/Method.h>
#include <Refureku/TypeInfo/Functions/StaticMethod.h>
#include <Refureku/TypeInfo/Variables/Field.h>
#include <Refureku/TypeInfo/Variables/StaticField.h>
#include <Refureku/TypeInfo/Archetypes/Enum.h>
#include <Refureku/TypeInfo/Archetypes/EnumValue.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateAPI.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererAPI.h>

namespace rfk { class Variable; class Function; }


#define ParseAllNested_GENERATED	\
public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct;\
REFUREKU_API virtual rfk::EEntityKind getTargetEntityKind() const noexcept override;\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::CodeGenerationHelpers;\
friend implements_template1__rfk_registerChildClass<ParseAllNested, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::CodeGenerationHelpers::registerChildClass<rfk::Property, ChildClass>(childClass);\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, ParseAllNested>) const_cast<rfk::Struct&>(thisClass).addSubclass(childClass);\
}\
\
\
public: REFUREKU_API static rfk::Class const& staticGetArchetype() noexcept;\
\
public: REFUREKU_API virtual rfk::Class const& getArchetype() const noexcept override;\
\
)\


#define File_ParseAllNested_GENERATED	\
template <> REFUREKU_API rfk::Archetype const* rfk::getArchetype<ParseAllNested>() noexcept;\


