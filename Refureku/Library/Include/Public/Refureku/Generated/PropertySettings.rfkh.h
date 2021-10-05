#pragma once

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Entity/EEntityKind.h>
#include <string>
#include <Refureku/Utility/CodeGenerationHelpers.h>
#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/TypeInfo/Functions/MethodAPI.h>
#include <Refureku/TypeInfo/Functions/StaticMethodAPI.h>
#include <Refureku/TypeInfo/Variables/FieldAPI.h>
#include <Refureku/TypeInfo/Variables/StaticFieldAPI.h>
#include <Refureku/TypeInfo/Archetypes/EnumAPI.h>
#include <Refureku/TypeInfo/Archetypes/EnumValueAPI.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateAPI.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererAPI.h>

namespace rfk { class VariableAPI; class FunctionAPI; }


#define PropertySettings_GENERATED	\
public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Struct | rfk::EEntityKind::Class;\
REFUREKU_API virtual rfk::EEntityKind getTargetEntityKind() const noexcept override;\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::CodeGenerationHelpers;\
friend implements_template1__rfk_registerChildClass<PropertySettings, void, void(rfk::StructAPI&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::StructAPI& childClass) noexcept {\
rfk::CodeGenerationHelpers::registerChildClass<rfk::Property, ChildClass>(childClass);\
rfk::StructAPI const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, PropertySettings>) const_cast<rfk::StructAPI&>(thisClass).addSubclass(childClass);\
}\
\
\
public: REFUREKU_API static rfk::ClassAPI const& staticGetArchetype() noexcept;\
\
public: REFUREKU_API virtual rfk::ClassAPI const& getArchetype() const noexcept override;\
\
)\


#define File_PropertySettings_GENERATED	\
template <> REFUREKU_API rfk::ArchetypeAPI const* rfk::getArchetypeAPI<PropertySettings>() noexcept;\


