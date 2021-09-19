#pragma once

#include "EntityMacros.h"

#include <Refureku/TypeInfo/Entity/EEntityKind.h>
#include <cstddef>

#include <Refureku/Utility/Macros.h>
#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/Utility/CodeGenerationHelpers.h>
#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>
#include <Refureku/TypeInfo/Archetypes/Class.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>
#include <Refureku/TypeInfo/Archetypes/ClassTemplate.h>
#include <Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h>
#include <Refureku/TypeInfo/Archetypes/ClassTemplateInstanceRegisterer.h>
namespace rfk {class NamespaceFragment;class Function;class Variable;}

#define File_Property_GENERATED	\


