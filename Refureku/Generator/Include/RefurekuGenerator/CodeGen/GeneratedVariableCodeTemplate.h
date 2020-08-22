/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/GeneratedCodeTemplate.h>
#include <Kodgen/InfoStructures/VariableInfo.h>

#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

namespace rfk
{
	class GeneratedVariableCodeTemplate : public GeneratedEntityCodeTemplate
	{
		private:
			/** Return generated macro name */
			std::string		generateGetVariableDefinition(kodgen::GeneratedFile&	generatedFile,
														  kodgen::VariableInfo const&	varInfo)	const	noexcept;

			std::string		generateRegistrationMacro(kodgen::GeneratedFile&	generatedFile,
													  kodgen::VariableInfo const&	varInfo)		const	noexcept;

			kodgen::uint8	computeVarFlags(kodgen::VariableInfo const& varInfo)					const	noexcept;

		protected:
			virtual void generateCode(kodgen::GeneratedFile&		generatedFile,
									  kodgen::EntityInfo const&		entityInfo,
									  kodgen::FileGenerationUnit&	fgu)			const noexcept override;

		public:
			GeneratedVariableCodeTemplate()										= default;
			GeneratedVariableCodeTemplate(GeneratedVariableCodeTemplate const&)	= default;
			GeneratedVariableCodeTemplate(GeneratedVariableCodeTemplate&&)		= default;
			virtual ~GeneratedVariableCodeTemplate()							= default;

			/**
			*	@brief Get the name of the getVariable generated function for the provided variable.
			*	
			*	@return The name of the getVariable generated function for the provided variable.
			*/
			static std::string getGetVariableFunctionName(kodgen::VariableInfo const& varInfo)	noexcept;
	};
}
