/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestClass.h"
#include "ConstructionTrackedClass.h"

#include "Generated/TestVariables.rfkh.h"

VARIABLE()
extern TestClass var_global_extern;

VARIABLE()
static int var_global_static;

VARIABLE()
extern int const var_global_extern_const;

VARIABLE()
extern ConstructionTrackedClass var_global_extern_constructionTracked;

VARIABLE()
extern ConstructionTrackedClass const var_global_extern_const_constructionTracked;

File_TestVariables_GENERATED