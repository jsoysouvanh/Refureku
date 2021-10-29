/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"

#include "Refureku/TypeInfo/Type.h"
#include "Refureku/TypeInfo/Database.h"
#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Entity/EntityCast.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"
#include "Refureku/TypeInfo/Namespace/Namespace.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/ParentStruct.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"
#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h"
#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h"
#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h"

#include "Refureku/NativeProperties.h"

#include "Refureku/Exceptions/ReturnTypeMismatch.h"
#include "Refureku/Exceptions/ArgCountMismatch.h"
#include "Refureku/Exceptions/ArgTypeMismatch.h"
#include "Refureku/Exceptions/ConstViolation.h"
#include "Refureku/Exceptions/BadNamespaceFormat.h"