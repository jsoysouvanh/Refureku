/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>
#include <functional>	//std::hash

#include <Kodgen/CodeGen/Macro/MacroCodeGenModule.h>

#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyCodeGen.h"
#include "RefurekuGenerator/Properties/PropertySettingsPropertyCodeGen.h"

namespace rfk
{
	class ReflectionCodeGenModule : public kodgen::MacroCodeGenModule
	{
		//private:
		//	/** Prefix used to build internal macros. Must match with GeneratedEntityCodeTemplate::internalPrefix. */
		//	static constexpr char const* const			_internalPrefix		= "__RFK";

		//	/** Name of the macro containing all native properties generated code. */
		//	static std::string const					_nativePropsMacroName;

		//	/** Class global string hasher. */
		//	static std::hash<std::string> const			_stringHasher;

		//	/** List of all namespaces we have generated metadata for. */
		//	std::vector<kodgen::NamespaceInfo const*>	_generatedNamespaces;

		//	/** List of all structs/classes we have generated metadata for. */
		//	std::vector<kodgen::StructClassInfo const*>	_generatedClasses;

		//	/** List of all enums we have generated metadata for. */
		//	std::vector<kodgen::EnumInfo const*>		_generatedEnums;

		//	/** List of all variables we have generated metadata for. */
		//	std::vector<kodgen::VariableInfo const*>	_generatedVariables;

		//	/** List of all functions we have generated metadata for. */
		//	std::vector<kodgen::FunctionInfo const*>	_generatedFunctions;

		//	/** List of all entities containing native properties. */
		//	std::vector<kodgen::EntityInfo const*>		_entitiesUsingNativeProperties;

		//	/**
		//	*	@brief Write the end file macro
		//	*
		//	*	@param file File to write to.
		//	*/
		//	void generateEndFileMacro(kodgen::GeneratedFile& file)								const	noexcept;

		//	/**
		//	*	@brief Save the entity to _entitiesUsingNativeProperties if it uses at least one native property.
		//	*	
		//	*	@param entityInfo Entity containing the properties to save.
		//	*/
		//	void saveEntitiesUsingNativeProperties(kodgen::EntityInfo const& entityInfo)				noexcept;

		//	/**
		//	*	@brief Generate code relative to attached native entities.
		//	*	
		//	*	@param file				File to write to.
		//	*	@param parsingResult	Structure containing info about the parsed file.
		//	*/
		//	void generateNativePropertiesCode(kodgen::GeneratedFile&			file,
		//									  kodgen::FileParsingResult const&	parsingResult)	const	noexcept;

		//protected:
		//	/**
		//	*	@return The name of the macro generated for the footer of each generated file.
		//	*/
		//	virtual std::string		getEndFileMacroName()														const	noexcept;

		//	virtual void			postGenerateFile(kodgen::FileParsingResult const& parsingResult)					noexcept override;

		//	virtual void			writeHeader(kodgen::GeneratedFile&				file,
		//										kodgen::FileParsingResult const&	parsingResult)				const	noexcept override;

		//	virtual void			writeFooter(kodgen::GeneratedFile&				file,
		//										kodgen::FileParsingResult const&	parsingResult)				const	noexcept override;

		//	virtual bool			writeEntityToFile(kodgen::GeneratedFile&			generatedFile,
		//											  kodgen::EntityInfo&				entityInfo,
		//											  kodgen::FileParsingResult const&	parsingResult,
		//											  kodgen::FileGenerationResult&		out_genResult)					noexcept override;

		//	virtual bool			writeNamespaceToFile(kodgen::GeneratedFile&				generatedFile,
		//												 kodgen::EntityInfo&				namespaceInfo,
		//												 kodgen::FileParsingResult const&	parsingResult,
		//												 kodgen::FileGenerationResult&		genResult)					noexcept override;

		//	virtual bool			writeStructOrClassToFile(kodgen::GeneratedFile&				generatedFile,
		//													 kodgen::EntityInfo&				structClassInfo,
		//													 kodgen::FileParsingResult const&	parsingResult,
		//													 kodgen::FileGenerationResult&		genResult)				noexcept override;

		//	virtual bool			writeEnumToFile(kodgen::GeneratedFile&				generatedFile,
		//											kodgen::EntityInfo&					enumInfo,
		//											kodgen::FileParsingResult const&	parsingResult,
		//											kodgen::FileGenerationResult&		genResult)						noexcept override;

		//	virtual bool			writeVariableToFile(kodgen::GeneratedFile&				generatedFile,
		//												kodgen::EntityInfo&					variableInfo,
		//												kodgen::FileParsingResult const&	parsingResult,
		//												kodgen::FileGenerationResult&		genResult)					noexcept override;

		//	virtual bool			writeFunctionToFile(kodgen::GeneratedFile&				generatedFile,
		//												kodgen::EntityInfo&					functionInfo,
		//												kodgen::FileParsingResult const&	parsingResult,
		//												kodgen::FileGenerationResult&		genResult)					noexcept override;

		private:
			/** Code generator for the CustomInstantiator property. */
			CustomInstantiatorPropertyCodeGen	_customInstantiatorProperty;

			/** Code generator for the PropertySettings property. */
			PropertySettingsPropertyCodeGen		_propertySettingsProperty;

			static std::hash<std::string>	_stringHasher;

			//Helper methods
			inline static std::string	getEntityId(kodgen::EntityInfo const& entity)	noexcept;

			//Generation methods
			/**
			*	TODO
			*/
			void	declareStaticGetArchetypeMethod(kodgen::StructClassInfo const&	structClass,
													kodgen::MacroCodeGenEnv&		env,
													std::string&					inout_result)				const	noexcept;

			/**
			*	TODO
			*/
			void	defineStaticGetArchetypeMethod(kodgen::StructClassInfo const&	structClass,
													kodgen::MacroCodeGenEnv&		env,
													std::string&					inout_result)				const	noexcept;

			/**
			*	TODO
			*/
			void	declareGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const&	structClass,
																 kodgen::MacroCodeGenEnv&		env,
																 std::string&					inout_result)	const	noexcept;

			/**
			*	TODO
			*/
			void	defineGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const&	structClass,
																 kodgen::MacroCodeGenEnv&		env,
																 std::string&					inout_result)	const	noexcept;

		protected:
			virtual ReflectionCodeGenModule*	clone()																const	noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateHeaderFileHeaderCode(kodgen::EntityInfo const*	entity,
																			 kodgen::MacroCodeGenEnv&	env,
																			 std::string&				inout_result)		noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateClassFooterCode(kodgen::EntityInfo const*	entity,
																		kodgen::MacroCodeGenEnv&	env,
																		std::string&				inout_result)			noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateSourceFileHeaderCode(kodgen::EntityInfo const*	entity,
																			 kodgen::MacroCodeGenEnv&	env,
																			 std::string&				inout_result)		noexcept	override;

		public:
			ReflectionCodeGenModule()								noexcept;
			ReflectionCodeGenModule(ReflectionCodeGenModule const&)	noexcept;
	};

	#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.inl"
}