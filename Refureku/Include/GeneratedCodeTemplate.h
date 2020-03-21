#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>
#include <InfoStructures/FieldInfo.h>

namespace refureku
{
	class GeneratedCodeTemplate : public kodgen::GeneratedCodeTemplate
	{
		private:
			void			undefMacros(kodgen::GeneratedFile& generatedFile, std::string const& generatedMacroName)	const	noexcept;
	
		protected:
			virtual void	generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo)	const	noexcept override;
	};
}
