#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>
#include <InfoStructures/StructClassInfo.h>
#include <InfoStructures/EnumInfo.h>

namespace refureku
{
	class GeneratedCodeTemplate : public kodgen::GeneratedCodeTemplate
	{
		private:
			void			undefMacros(kodgen::GeneratedFile& generatedFile, std::string const& generatedMacroName)			const	noexcept;

			void			generateClassCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& classInfo)	const	noexcept;
			void			generateStructCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& structInfo)	const	noexcept;
			void			generateEnumCode(kodgen::GeneratedFile& generatedFile, kodgen::EnumInfo const& enumInfo)			const	noexcept;

		protected:
			virtual void	generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo)			const	noexcept override;
	};
}
