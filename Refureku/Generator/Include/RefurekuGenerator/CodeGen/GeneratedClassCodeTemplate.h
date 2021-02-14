/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include <Kodgen/InfoStructures/StructClassInfo.h>

#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"

namespace rfk
{
	class GeneratedClassCodeTemplate : public GeneratedEntityCodeTemplate
	{
		private:
			void						generateClassCode(kodgen::GeneratedFile&	generatedFile,
														  kodgen::StructClassInfo&	classInfo)								const	noexcept;
			void						generateStructCode(kodgen::GeneratedFile&	generatedFile,
														   kodgen::StructClassInfo&	structInfo)								const	noexcept;

			kodgen::uint16				computeMethodFlags(kodgen::MethodInfo const& method)								const	noexcept;
			kodgen::uint16				computeFieldFlags(kodgen::FieldInfo const& field)									const	noexcept;
			std::string					getFullMethodPrototype(kodgen::StructClassInfo const&	classInfo,
															   kodgen::MethodInfo const&		method)						const	noexcept;

			/**
			*	@brief Generate the macro containing the getArchetype definition.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateGetArchetypeMacro(kodgen::GeneratedFile&			generatedFile,
																  kodgen::StructClassInfo&	info)							const	noexcept;
			
			/**
			*	@brief Generate the macro containing the properties definition of this struct/class.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateArchetypePropertiesMacro(kodgen::GeneratedFile&		generatedFile,
																		 kodgen::EntityInfo const&	info)					const	noexcept;
			
			/**
			*	@brief Generate the macro containing the database registration logic.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateRegistrationMacro(kodgen::GeneratedFile&			generatedFile,
																  kodgen::StructClassInfo const&	info)					const	noexcept;
			
			/**
			*	@brief Generate the macro containing all the code relative to native properties used within this class.
			*	
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*	
			*	@return The name of the generated macro.
			*/
			std::string					generateNativePropsMacro(kodgen::GeneratedFile&			generatedFile,
																 kodgen::StructClassInfo const&	info)						const	noexcept;

			/**
			*	@brief Generate the macro containing the parents definition.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateParentsMetadataMacro(kodgen::GeneratedFile&			generatedFile,
																	 kodgen::StructClassInfo const&	info)				const	noexcept;
			
			/**
			*	@brief Generate the macro containing the nested structs/classes/enums definition.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateNestedArchetypesMetadataMacro(kodgen::GeneratedFile&			generatedFile,
																			  kodgen::StructClassInfo&	info)			const	noexcept;

			/**
			*	@brief Generate the macro containing the default instantiator setup.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateRegisterDefaultInstantiator(kodgen::GeneratedFile&		generatedFile,
																			kodgen::StructClassInfo&	info)			const	noexcept;

			/**
			*	@brief Generate the (2) macros containing fields definition.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The names of the (2) generated macros.
			*/
			std::array<std::string, 2>	generateFieldsMetadataMacros(kodgen::GeneratedFile&		generatedFile,
																	 kodgen::StructClassInfo&	info)					const	noexcept;
			
			/**
			*	@brief Generate the macro containing the methods definition.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateMethodsMetadataMacro(kodgen::GeneratedFile&		generatedFile,
																	 kodgen::StructClassInfo&	info)					const	noexcept;
			
			/**
			*	@brief Generate the macro containing field inheritance function definition.
			*
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*
			*	@return The name of the generated macro.
			*/
			std::string					generateFieldHelperMethodsMacro(kodgen::GeneratedFile&		generatedFile,
																		 kodgen::StructClassInfo&	info)				const	noexcept;

		protected:
			virtual void						generateCode(kodgen::GeneratedFile&			generatedFile,
															 kodgen::EntityInfo&			entityInfo,
															 kodgen::FileGenerationUnit&	fgu,
															 std::string&					out_errorDescription)	const	noexcept override;

			/**
			*	@brief Generate macros containing code that will be injected in the main macro.
			*			/!\ All generated macro names must be unique to avoid collision with other generated macros,
			*				thus it is recommended that it contains the entity id in its name (retrieved with getEntityId(info)).
			*	
			*	@param generatedFile	File to write into.
			*	@param info				Struct/Class info.
			*	
			*	@return A collection of all generated macro names.
			*/
			virtual std::vector<std::string>	generateCustomCodeMacros(kodgen::GeneratedFile&		generatedFile,
																		 kodgen::StructClassInfo&	info)			const	noexcept;

			/**
			*	@return The name of the main macro which will be generated and injected in the class.
			*/
			virtual std::string					getMainMacroName(kodgen::StructClassInfo& info)						const	noexcept;

		public:
			GeneratedClassCodeTemplate()									= default;
			GeneratedClassCodeTemplate(GeneratedClassCodeTemplate const&)	= default;
			GeneratedClassCodeTemplate(GeneratedClassCodeTemplate&&)		= default;
			virtual ~GeneratedClassCodeTemplate()							= default;
	};
}
