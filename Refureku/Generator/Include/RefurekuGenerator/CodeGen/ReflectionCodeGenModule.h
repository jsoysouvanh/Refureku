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
#include <unordered_map>

#include <Kodgen/CodeGen/Macro/MacroCodeGenModule.h>

#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyCodeGen.h"
#include "RefurekuGenerator/Properties/PropertySettingsPropertyCodeGen.h"

namespace rfk
{
	class ReflectionCodeGenModule : public kodgen::MacroCodeGenModule
	{
		private:
			/** Code generator for the CustomInstantiator property. */
			CustomInstantiatorPropertyCodeGen		_customInstantiatorProperty;

			/** Code generator for the PropertySettings property. */
			PropertySettingsPropertyCodeGen			_propertySettingsProperty;

			/** Class global string hasher. */
			static std::hash<std::string>			_stringHasher;

			/** Dictionnary used to generate properties code. */
			std::unordered_map<std::string, int>	_propertiesCount;

			/**
			*	@brief Compute the unique id of an entity. The returned string contains an unsigned integer.
			*
			*	@param entity The target entity.
			* 
			*	@return The unique ID of an entity as a string.
			*/
			inline static std::string	getEntityId(kodgen::EntityInfo const& entity)							noexcept;

			/**
			*	@brief Convert the name of a kodgen::EEntityType to its equivalent rfk::EEntityKind name.
			* 
			*	@param entityType The kodgen::EEntityType value to convert.
			* 
			*	@return The name of the equivalent rfk::EEntityKind value.
			*/
			static std::string			convertEntityTypeToEntityKind(kodgen::EEntityType entityType)			noexcept;

			/**
			*	@brief Compute the rfk::EFieldFlags value for the provided field.
			*
			*	@param field Field used to compute the rfk::EFieldFlags value.
			* 
			*	@return The computed rfk::FieldFlags value as a uint16.
			*/
			static kodgen::uint16		computeRefurekuFieldFlags(kodgen::FieldInfo const& field)				noexcept;

			/**
			*	@brief Compute the rfk::EMethodFlags value for the provided method.
			*
			*	@param method Method used to compute the rfk::EMethodFlags value.
			* 
			*	@return The computed rfk::EMethodFlags value as a uint16.
			*/
			static kodgen::uint16		computeRefurekuMethodFlags(kodgen::MethodInfo const& method)			noexcept;

			/**
			*	@brief	Compute the full type of a method pointer.
			*			Ex: void method(int){} becomes void (*)(int)
			*			Ex: class A { void method(int){} }; becomes void (A::*)(int)
			*
			*	@param method Method used to compute the rfk::EMethodFlags value.
			* 
			*	@return The computed rfk::EMethodFlags value as a uint16.
			*/
			static std::string			computeFullMethodPointerType(kodgen::StructClassInfo const&	classInfo,
																	 kodgen::MethodInfo const&		method)		noexcept;

			/**
			*	TODO
			*/
			void	fillEntityProperties(kodgen::EntityInfo const&	entity,
										 kodgen::MacroCodeGenEnv&	env,
										 std::string const&			generatedEntityVarName,
										 std::string&				inout_result)										noexcept;

			/**
			*	@brief Generate the headers inclusion code for the generated header file.
			* 
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	includeHeaderFileHeaders(kodgen::MacroCodeGenEnv&	env,
											 std::string&				inout_result)							const	noexcept;

			/**
			*	@brief Generate the headers inclusion code for the generated source file.
			* 
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	includeSourceFileHeaders(kodgen::MacroCodeGenEnv&	env,
											 std::string&				inout_result)							const	noexcept;


			//Struct / Class code generation
			/**
			*	@brief Generate the friend statements for the provided class.
			* 
			*	@param structClass	Target struct/class.
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	declareFriendClasses(kodgen::StructClassInfo const&	structClass,
										 kodgen::MacroCodeGenEnv&		env,
										 std::string&					inout_result)							const	noexcept;

			/**
			*	@brief Generate the staticGetArchetype method declaration.
			* 
			*	@param structClass	Target struct/class.
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	declareStaticGetArchetypeMethod(kodgen::StructClassInfo const&	structClass,
													kodgen::MacroCodeGenEnv&		env,
													std::string&					inout_result)				const	noexcept;

			/**
			*	@brief Generate the staticGetArchetype method definition.
			* 
			*	@param structClass	Target struct/class.
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	defineStaticGetArchetypeMethod(kodgen::StructClassInfo const&	structClass,
													kodgen::MacroCodeGenEnv&		env,
													std::string&					inout_result)						noexcept;

			/**
			*	TODO
			*/
			void	fillClassParentsMetadata(kodgen::StructClassInfo const&	structClass,
											 kodgen::MacroCodeGenEnv&		env,
											 std::string const&				generatedEntityVarName,
											 std::string&					inout_result)								noexcept;

			/**
			*	TODO
			*/
			void	fillClassFields(kodgen::StructClassInfo const&	structClass,
									kodgen::MacroCodeGenEnv&		env,
									std::string						generatedClassRefExpression,
									std::string&					inout_result)										noexcept;

			/**
			*	TODO
			*/
			void	fillClassMethods(kodgen::StructClassInfo const&	structClass,
									 kodgen::MacroCodeGenEnv&		env,
									 std::string const&				generatedEntityVarName,
									 std::string&					inout_result)										noexcept;

			/**
			*	TODO
			*/
			void	fillClassNestedArchetypes(kodgen::StructClassInfo const&	structClass,
											  kodgen::MacroCodeGenEnv&			env,
											  std::string const&				generatedEntityVarName,
											  std::string&						inout_result)							noexcept;

			/**
			*	@brief Generate the getArchetype method declaration if the provided class inherits from rfk::Object.
			* 
			*	@param structClass	Target struct/class.
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	declareGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const&	structClass,
																 kodgen::MacroCodeGenEnv&		env,
																 std::string&					inout_result)	const	noexcept;

			/**
			*	@brief Generate the getArchetype method definition if the provided class inherits from rfk::Object.
			* 
			*	@param structClass	Target struct/class.
			*	@param env			Code generation environment.
			*	@param inout_result	String to append the generated code.
			*/
			void	defineGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const&	structClass,
																 kodgen::MacroCodeGenEnv&		env,
																 std::string&					inout_result)	const	noexcept;

			/**
			*	TODO
			*/
			void	declareGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const&	structClass,
															  kodgen::MacroCodeGenEnv&			env,
															  std::string&						inout_result)	const	noexcept;

			/**
			*	TODO
			*/
			void	defineGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const&	structClass,
															 kodgen::MacroCodeGenEnv&		env,
															 std::string&					inout_result)		const	noexcept;

			/**
			*	TODO
			*/
			void	declareAndDefineRegisterChildClassMethod(kodgen::StructClassInfo const&	structClass,
															 kodgen::MacroCodeGenEnv&		env,
															 std::string&					inout_result)				noexcept;

			/**
			*	TODO
			*/
			void	declareClassRegistrationField(kodgen::StructClassInfo const&	structClass,
												  kodgen::MacroCodeGenEnv&			env,
												  std::string&						inout_result)				const	noexcept;

			/**
			*	TODO
			*/
			void	defineClassRegistrationField(kodgen::StructClassInfo const&	structClass,
												 kodgen::MacroCodeGenEnv&			env,
												 std::string&						inout_result)				const	noexcept;



			//Enums code generation
			/**
			*	TODO
			*/
			void	declareGetEnumTemplateSpecialization(kodgen::EnumInfo const&	enum_,
														 kodgen::MacroCodeGenEnv&	env,
														 std::string&				inout_result)		const	noexcept;

			/**
			*	TODO
			*/
			void	defineGetEnumTemplateSpecialization(kodgen::EnumInfo const&		enum_,
														kodgen::MacroCodeGenEnv&	env,
														std::string&				inout_result)				noexcept;

			/**
			*	TODO
			*/
			void	declareEnumRegistrationVariable(kodgen::EnumInfo const&	enum_,
													kodgen::MacroCodeGenEnv&	env,
													std::string&				inout_result)			const	noexcept;

			/**
			*	TODO
			*/
			void	defineEnumRegistrationVariable(kodgen::EnumInfo const&	enum_,
												   kodgen::MacroCodeGenEnv&	env,
												   std::string&				inout_result)				const	noexcept;

		protected:
			virtual ReflectionCodeGenModule*	clone()																const	noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateHeaderFileHeaderCode(kodgen::EntityInfo const*	entity,
																			 kodgen::MacroCodeGenEnv&	env,
																			 std::string&				inout_result)		noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateClassFooterCode(kodgen::EntityInfo const*	entity,
																		kodgen::MacroCodeGenEnv&	env,
																		std::string&				inout_result)			noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateHeaderFileFooterCode(kodgen::EntityInfo const*	entity,
																			 kodgen::MacroCodeGenEnv&	env,
																			 std::string&				inout_result)		noexcept	override;

			virtual kodgen::ETraversalBehaviour	generateSourceFileHeaderCode(kodgen::EntityInfo const*	entity,
																			 kodgen::MacroCodeGenEnv&	env,
																			 std::string&				inout_result)		noexcept	override;

		public:
			ReflectionCodeGenModule()								noexcept;
			ReflectionCodeGenModule(ReflectionCodeGenModule const&)	noexcept;
	};

	#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.inl"
}