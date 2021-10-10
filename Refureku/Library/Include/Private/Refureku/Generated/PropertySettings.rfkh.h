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
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h>
#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h>
#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h>
#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h>

namespace rfk { class Variable; class Function; }


#define PropertySettings_GENERATED	\
public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Struct | rfk::EEntityKind::Class;\
 virtual rfk::EEntityKind getTargetEntityKind() const noexcept override;\
RFK_UNPACK_IF_NOT_PARSING(friend rfk::CodeGenerationHelpers;\
friend implements_template1__rfk_registerChildClass<PropertySettings, void, void(rfk::Struct&)>; \
\
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::CodeGenerationHelpers::registerChildClass<rfk::Property, ChildClass>(childClass);\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, PropertySettings>) const_cast<rfk::Struct&>(thisClass).addSubclass(childClass);\
}\
\
\
public:  static rfk::Class const& staticGetArchetype() noexcept;\
\
public:  virtual rfk::Class const& getArchetype() const noexcept override;\
\
)\


#define File_PropertySettings_GENERATED	\
template <>  rfk::Archetype const* rfk::getArchetype<PropertySettings>() noexcept;\


