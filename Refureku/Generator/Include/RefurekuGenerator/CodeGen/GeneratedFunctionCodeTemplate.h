/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/GeneratedCodeTemplate.h>
#include <Kodgen/InfoStructures/FunctionInfo.h>

#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

namespace rfk
{
	class GeneratedFunctionCodeTemplate : public GeneratedEntityCodeTemplate
	{
		private:
			/** Return generated macro name */
			std::string		generateGetFunctionDefinition(kodgen::GeneratedFile&		generatedFile,
														  kodgen::FunctionInfo const&	funcInfo)		const	noexcept;

			std::string		generateRegistrationMacro(kodgen::GeneratedFile&		generatedFile,
													  kodgen::FunctionInfo const&	funcInfo)			const	noexcept;

			kodgen::uint8	computeFunctionFlags(kodgen::FunctionInfo const& funcInfo)					const	noexcept;

		protected:
			virtual void generateCode(kodgen::GeneratedFile&			generatedFile,
									  kodgen::EntityInfo&				entityInfo,
									  kodgen::FileGenerationUnit&		fgu,
									  kodgen::FileParsingResult const&	parsingResult,
									  std::string&						out_errorDescription)	const noexcept override;

		public:
			GeneratedFunctionCodeTemplate()										= default;
			GeneratedFunctionCodeTemplate(GeneratedFunctionCodeTemplate const&)	= default;
			GeneratedFunctionCodeTemplate(GeneratedFunctionCodeTemplate&&)		= default;
			virtual ~GeneratedFunctionCodeTemplate()							= default;

			/**
			*	@brief Get the name of the getFunction generated function for the provided function.
			*	
			*	@return The name of the getFunction generated function for the provided function.
			*/
			static std::string getGetFunctionFunctionName(kodgen::FunctionInfo const& funcInfo)	noexcept;
	};
}
