/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/GeneratedCodeTemplate.h>
#include <Kodgen/InfoStructures/EnumInfo.h>

#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

namespace rfk
{
	class GeneratedEnumCodeTemplate : public GeneratedEntityCodeTemplate
	{
		private:
			void generateEnumCode(kodgen::GeneratedFile&	generatedFile,
								  kodgen::EnumInfo const&	enumInfo)							const	noexcept;

			/** Return generated macro name */
			std::string generateGetEnumSpecialization(kodgen::GeneratedFile&	generatedFile,
													  kodgen::EnumInfo const&	enumInfo)		const	noexcept;
			
			std::string generateRegistrationMacro(kodgen::GeneratedFile&	generatedFile,
												  kodgen::EnumInfo const&	enumInfo)			const	noexcept;

		protected:
			virtual void generateCode(kodgen::GeneratedFile&		generatedFile,
									  kodgen::EntityInfo&			entityInfo,
									  kodgen::FileGenerationUnit&	fgu,
									  std::string&					out_errorDescription)	const noexcept override;

		public:
			GeneratedEnumCodeTemplate()									= default;
			GeneratedEnumCodeTemplate(GeneratedEnumCodeTemplate const&)	= default;
			GeneratedEnumCodeTemplate(GeneratedEnumCodeTemplate&&)		= default;
			virtual ~GeneratedEnumCodeTemplate()						= default;
	};
}
