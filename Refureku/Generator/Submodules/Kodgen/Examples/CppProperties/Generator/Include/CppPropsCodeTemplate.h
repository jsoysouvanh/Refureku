#pragma once

#include <Kodgen/CodeGen/GeneratedCodeTemplate.h>
#include <Kodgen/InfoStructures/FieldInfo.h>

class CppPropsCodeTemplate : public kodgen::GeneratedCodeTemplate
{
	private:
		std::string generateGetter(kodgen::FieldInfo const&			fieldInfo,
								   kodgen::ComplexProperty const&	complexProp)	const	noexcept;
		std::string generateSetter(kodgen::FieldInfo const&			fieldInfo,
								   kodgen::ComplexProperty const&	complexProp)	const	noexcept;

		void		undefMacros(kodgen::GeneratedFile&	generatedFile,
								std::string const&		generatedMacroName)			const	noexcept;

	protected:
		virtual void generateCode(kodgen::GeneratedFile&		generatedFile,
								  kodgen::EntityInfo const&		entityInfo,
								  kodgen::FileGenerationUnit&	fgu,
								  std::string&					out_errorDescription)	const noexcept override;
};