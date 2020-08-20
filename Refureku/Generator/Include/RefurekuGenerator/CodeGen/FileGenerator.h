/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/FileGenerator.h>

#include "RefurekuGenerator/CodeGen/GeneratedNamespaceCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedClassCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedEnumCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedVariableCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedFunctionCodeTemplate.h"

namespace rfk
{
	class FileGenerator : public kodgen::FileGenerator
	{
		private:
			/** Code templates used by this generator. */
			GeneratedNamespaceCodeTemplate	_namespaceCodeTemplate;
			GeneratedClassCodeTemplate		_classCodeTemplate;
			GeneratedEnumCodeTemplate		_enumCodeTemplate;
			GeneratedVariableCodeTemplate	_variableCodeTemplate;
			GeneratedFunctionCodeTemplate	_functionCodeTemplate;

		public:
			FileGenerator()						noexcept;
			FileGenerator(FileGenerator const&)	= default;
			FileGenerator(FileGenerator&&)		= default;
			virtual ~FileGenerator()			= default;
	};
}