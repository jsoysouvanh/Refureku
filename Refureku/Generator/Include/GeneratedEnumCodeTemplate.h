#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>
#include <InfoStructures/EnumInfo.h>

#include "GeneratedEntityCodeTemplate.h"

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
			virtual void generateCode(kodgen::GeneratedFile&	generatedFile,
									  kodgen::EntityInfo const&	entityInfo)		const noexcept override;
	};
}
