#pragma once

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Entity/EEntityKind.h>
#include <cstddef>

#include <Refureku/Utility/Macros.h>
#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/Utility/CodeGenerationHelpers.h>
#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>
#include <Refureku/TypeInfo/Archetypes/Class.h>
#include <Refureku/TypeInfo/Archetypes/ClassTemplate.h>
#include <Refureku/TypeInfo/Archetypes/ClassTemplateInstantiation.h>
#include <Refureku/TypeInfo/Archetypes/ClassTemplateInstantiationRegisterer.h>
namespace rfk {class Function;class Variable;}

#define ParseAllNested_GENERATED	\
public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct;\
REFUREKU_API virtual rfk::EEntityKind getTargetEntityKind() const noexcept override;\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::Struct;\
friend rfk::CodeGenerationHelpers;\
friend implements_template1__rfk_registerChildClass<ParseAllNested, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::CodeGenerationHelpers::registerChildClass<rfk::Property, ChildClass>(childClass);\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, ParseAllNested>) const_cast<rfk::Struct&>(thisClass).subclasses.insert(&childClass);\
}\
\
\
public: REFUREKU_API static rfk::Struct const& staticGetArchetype() noexcept;\
\
public: REFUREKU_API virtual rfk::Struct const& getArchetype() const noexcept override;\
\
)\


#define File_ParseAllNested_GENERATED	\
template <> REFUREKU_API rfk::Archetype const* rfk::getArchetype<ParseAllNested>() noexcept;\


