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
#include <unordered_set>

#include <Kodgen/CodeGen/Macro/MacroCodeGenModule.h>
#include "Kodgen/InfoStructures/EnumInfo.h"

#include "RefurekuGenerator/Properties/InstantiatorPropertyCodeGen.h"
#include "RefurekuGenerator/Properties/PropertySettingsPropertyCodeGen.h"

namespace rfk
{
	class ReflectionCodeGenModule : public kodgen::MacroCodeGenModule
	{
		private:
		/** Class global string hasher. */
		static std::hash<std::string>				_stringHasher;

		/** Code generator for the CustomInstantiator property. */
		InstantiatorPropertyCodeGen					_instantiatorProperty;

		/** Code generator for the PropertySettings property. */
		PropertySettingsPropertyCodeGen				_propertySettingsProperty;

		/** Dictionnary used to generate properties code. */
		std::unordered_map<std::string, int>		_propertiesCount;

		/** Flag that determines whether the currently generated code is hidden from the parser or not. */
		bool										_isGeneratingHiddenCode;

		/** List of non-public enums. */
		std::unordered_set<kodgen::EnumInfo const*>	_nonPublicEnums;

		/**
		*	@brief Compute the unique id of an entity. The returned string contains an unsigned integer.
		*
		*	@param entity The target entity.
		* 
		*	@return The unique ID of an entity as a string.
		*/
		inline static std::string	getEntityId(kodgen::EntityInfo const& entity)										noexcept;

		/**
		*	@brief Convert the name of a kodgen::EEntityType to its equivalent rfk::EEntityKind name.
		* 
		*	@param entityType The kodgen::EEntityType value to convert.
		* 
		*	@return The name of the equivalent rfk::EEntityKind value.
		*/
		static std::string			convertEntityTypeToEntityKind(kodgen::EEntityType entityType)						noexcept;

		/**
		*	@brief Compute the rfk::EFieldFlags value for the provided field.
		*
		*	@param field Field used to compute the rfk::EFieldFlags value.
		* 
		*	@return The computed rfk::FieldFlags value as a uint16.
		*/
		static kodgen::uint16		computeRefurekuFieldFlags(kodgen::FieldInfo const& field)							noexcept;

		/**
		*	@brief Compute the rfk::EMethodFlags value for the provided method.
		*
		*	@param method Method used to compute the rfk::EMethodFlags value.
		* 
		*	@return The computed rfk::EMethodFlags value as a uint16.
		*/
		static kodgen::uint16		computeRefurekuMethodFlags(kodgen::MethodInfo const& method)						noexcept;

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
																 kodgen::MethodInfo const&		method)					noexcept;

		/**
		*	@brief Compute the rfk::EVarFlags value for the provided variable.
		*
		*	@param variable Variable used to compute the rfk::EVarFlags value.
		* 
		*	@return The computed rfk::EVarFlags value as a uint8.
		*/
		static kodgen::uint8		computeRefurekuVariableFlags(kodgen::VariableInfo const& variable)					noexcept;

		/**
		*	@brief Compute the name of the getVariable function for the given variable.
		* 
		*	@param variable The target variable.
		* 
		*	@return The name of the getVariable function for the target variable.
		*/
		static std::string			computeGetVariableFunctionName(kodgen::VariableInfo const& variable)				noexcept;

		/**
		*	@brief Compute the rfk::EFunctionFlags value for the provided function.
		*
		*	@param function Function used to compute the rfk::EFunctionFlags value.
		* 
		*	@return The computed rfk::EFunctionFlags value as a uint8.
		*/
		static kodgen::uint8		computeRefurekuFunctionFlags(kodgen::FunctionInfo const& function)					noexcept;

		/**
		*	@brief Compute the name of the getFunction function for the given function.
		* 
		*	@param function The target function.
		* 
		*	@return The name of the getFunction function for the target function.
		*/
		static std::string			computeGetFunctionFunctionName(kodgen::FunctionInfo const& function)		noexcept;

		/**
		*	@brief Compute the name of the getNamespaceFragment function for the given namespace.
		* 
		*	@param namespace_	The target namespace.
		*	@param sourceFile	The path to the file the namespace comes from.
		* 
		*	@return The name of the getNamespaceFragment function for the target namespace.
		*/
		static std::string			computeGetNamespaceFragmentFunctionName(kodgen::NamespaceInfo const&	namespace_,
																			fs::path const&					sourceFile)	noexcept;

		/**
		*	@brief Compute the name of the registerer variable for the given namespace.
		* 
		*	@param namespace_	The target namespace.
		*	@param sourceFile	The path to the file the namespace comes from.
		* 
		*	@return The name of the registerer variable for the target namespace.
		*/
		static std::string			computeNamespaceFragmentRegistererName(kodgen::NamespaceInfo const&	namespace_,
																		   fs::path const&				sourceFile)		noexcept;

		/**
		*	@brief Compute the name of the generated variable for the provided property.
		* 
		*	@param entity	Entity the property is attached to.
		*	@param propertyIndex	Index of the target property in the entity's properties array.
		* 
		*	@return The name of the generated variable name for the target property.
		*/
		static std::string			computePropertyVariableName(kodgen::EntityInfo const&	entity,
																kodgen::uint8				propertyIndex)				noexcept;

		/**
		*	@brief Compute the name of the generated method to get a non-public nested enum.
		* 
		*	@param nestedEnum The target nested enum.
		* 
		*	@return The name of the generated method.
		*/
		static std::string			computeGetNestedEnumMethodName(kodgen::NestedEnumInfo const& nestedEnum)			noexcept;

		/**
		*	@brief Check if the provided class is accessible from anywhere in the program.
		* 
		*	@param class_ The target class.
		* 
		*	@return true if the class is public, else false.
		*/
		static bool					isPublicClass(kodgen::StructClassInfo const& class_)								noexcept;

		/**
		*	@brief Compute the code that will be evaluated to the provided entity id in the generated code.
		* 
		*	@param class_ The reference class template.
		*	@param entity The target entity.
		* 
		*	@return The code that will be evaluated the provided entity id in the generated code.
		*/
		static std::string			computeClassTemplateEntityId(kodgen::StructClassInfo const& class_,
																 kodgen::EntityInfo const&		entity)					noexcept;

		/**
		*	@brief	Compute the id of a class nested entity.
		*			The returned string will be evaluated to an id in the generated code.
		* 
		*	@param className	Name of the class.
		*	@param entity		The class nested entity.
		* 
		*	@return The code that will be evaluated to an id in the generated code.
		*/
		static std::string			computeClassNestedEntityId(std::string					className,
															   kodgen::EntityInfo const&	entity)						noexcept;

		/**
		*	@brief	All code generated from this point will be hidden to the parser.
		*			This means the generated code can't be reflected.
		* 
		*	@param env			Code generation environment.
		*	@param inout_result	String to append the generated code.
		*/
		void	beginHiddenGeneratedCode(kodgen::MacroCodeGenEnv&	env,
										 std::string&				inout_result)									noexcept;

		/**
		*	@brief	End the hidden generated code section. If beginHiddenGeneratedCode hasn't been called before,
		*			nothing happens.
		* 
		*	@param env			Code generation environment.
		*	@param inout_result	String to append the generated code.
		*/
		void	endHiddenGeneratedCode(kodgen::MacroCodeGenEnv&	env,
									   std::string&				inout_result)										noexcept;

		/**
		*	@brief Reset the module to begin a clean generation from scratch.
		*/
		void	reset()																								noexcept;

		/**
		*	@brief	Check that the endHiddenGeneratedCode has been called correctly if there was any previous
		*			call to beginHiddenGeneratedCode.
		*			If it is not the case, the code will assert.
		*/
		void	checkHiddenGeneratedCodeState()																const	noexcept;

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
		void	fillClassParents(kodgen::StructClassInfo const&	structClass,
								 kodgen::MacroCodeGenEnv&		env,
								 std::string const&				generatedEntityVarName,
								 std::string&					inout_result)										noexcept;

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
		void	declareGetNestedEnumMethods(kodgen::StructClassInfo const&	structClass,
											kodgen::MacroCodeGenEnv&		env,
											std::string&					inout_result)							noexcept;

		/**
		*	TODO
		*/
		void	defineGetNestedEnumMethods(kodgen::StructClassInfo const&	structClass,
										   kodgen::MacroCodeGenEnv&		env,
										   std::string&					inout_result)							noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineClassRegistererVariable(kodgen::StructClassInfo const&	structClass,
														kodgen::MacroCodeGenEnv&		env,
														std::string&					inout_result)		const	noexcept;

		//Class template code generation
		/**
		*	TODO
		*/
		void	declareAndDefineClassTemplateStaticGetArchetypeMethod(kodgen::StructClassInfo const&	structClass,
																	  kodgen::MacroCodeGenEnv&			env,
																	  std::string&						inout_result)						noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineClassTemplateGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const&	structClass,
																				   kodgen::MacroCodeGenEnv&			env,
																				   std::string&						inout_result)	const	noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineClassTemplateRegistererField(kodgen::StructClassInfo const&	structClass,
															 kodgen::MacroCodeGenEnv&		env,
															 std::string&					inout_result)							const	noexcept;

		/**
		*	TODO
		*/
		void	fillClassTemplateArguments(kodgen::StructClassInfo const&	structClass,
										   std::string						generatedEntityVarName,
										   kodgen::MacroCodeGenEnv&			env,
										   std::string&						inout_result)											const	noexcept;

		/**
		*	TODO
		*/
		void	defineClassTemplateGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const&	structClass,
																	  kodgen::MacroCodeGenEnv&			env,
																	  std::string&						inout_result)						noexcept;

		/**
		*	@brief Generate code to create and add a template parameter to the provided object.
		* 
		*	@param templateParam	Template parameter to create/add.
		*	@param generatedVarName	Name of the variable generated for the template parameter.
		*	@param objVarName		Name of the generated variable to add the template parameter to.
		*	@param addFuncName		Name of the function to use to add the parameter to the object.
		*	@param env				Code generation environment.
		*	@param inout_result		String to append the generated code.
		*	@param recursionLevel	Number of times this function has been recursively called.
		*/
		void	addTemplateParameter(kodgen::TemplateParamInfo const&	templateParam,
									 std::string						generatedVarName,
									 std::string const&					objVarName,
									 std::string						addFuncName,
									 kodgen::MacroCodeGenEnv&			env,
									 std::string&						inout_result,
									 int								recursionLevel = 0)											const	noexcept;

		/**
		*	TODO
		*/
		void	fillClassTemplateParameters(kodgen::StructClassInfo const&	structClass,
											std::string						classTemplateVarName,
											kodgen::MacroCodeGenEnv&		env,
											std::string&					inout_result)											const	noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineClassTemplateRegistererVariable(kodgen::StructClassInfo const&	structClass,
																kodgen::MacroCodeGenEnv&		env,
																std::string&					inout_result)						const	noexcept;

		//Enums code generation
		/**
		*	@brief Check whether the target enum has been registered to the _nonPublicEnum set or not.
		* 
		*	@param nestedEnum the target enum.
		* 
		*	@return true if the nestedEnum is non-public, else false.
		*/
		bool	isRegisteredNonPublicEnum(kodgen::EnumInfo const& nestedEnum)					const	noexcept;

		/**
		*	TODO
		*/
		void	declareGetEnumTemplateSpecialization(kodgen::EnumInfo const&	enum_,
													 kodgen::MacroCodeGenEnv&	env,
													 std::string&				inout_result)	const	noexcept;

		/**
		*	TODO
		*/
		void	defineGetEnumTemplateSpecialization(kodgen::EnumInfo const&		enum_,
													kodgen::MacroCodeGenEnv&	env,
													std::string&				inout_result)			noexcept;

		/**
		*	@brief	Define the content of a get enum method from the { to the }.
		*			Does not include the method prototype.
		* 
		*	TODO
		*/
		void	defineGetEnumContent(kodgen::EnumInfo const&	enum_,
									 kodgen::MacroCodeGenEnv&	env,
									 std::string&				inout_result)							noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineEnumRegistererVariable(kodgen::EnumInfo const&	enum_,
													   kodgen::MacroCodeGenEnv&	env,
													   std::string&				inout_result)	const	noexcept;


		//Variables code generation
		/**
		*	TODO
		*/
		void	declareGetVariableFunction(kodgen::VariableInfo const&	variable,
										   kodgen::MacroCodeGenEnv&		env,
										   std::string&					inout_result)					noexcept;

		/**
		*	TODO
		*/
		void	defineGetVariableFunction(kodgen::VariableInfo const&	variable,
										  kodgen::MacroCodeGenEnv&		env,
										  std::string&					inout_result)					noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineVariableRegistererVariable(kodgen::VariableInfo const&	variable,
														   kodgen::MacroCodeGenEnv&		env,
														   std::string&					inout_result)	noexcept;



		//Functions code generation
		/**
		*	TODO
		*/
		void	declareGetFunctionFunction(kodgen::FunctionInfo const&	function,
										   kodgen::MacroCodeGenEnv&		env,
										   std::string&					inout_result)					noexcept;

		/**
		*	TODO
		*/
		void	defineGetFunctionFunction(kodgen::FunctionInfo const&	function,
										  kodgen::MacroCodeGenEnv&		env,
										  std::string&					inout_result)					noexcept;

		/**
		*	TODO
		*/
		void	declareAndDefineFunctionRegistererVariable(kodgen::FunctionInfo const&	function,
														   kodgen::MacroCodeGenEnv&		env,
														   std::string&					inout_result)	noexcept;



		//Namespaces code generation
		/**
		*	@brief Declare and define the getNamespaceFragment function for the provided namespace.
		*
		*	@param namespace_	Target namespace.
		*	@param env			Code generation environment.
		*	@param inout_result	String to append the generated code.
		*/
		void	declareAndDefineGetNamespaceFragmentFunction(kodgen::NamespaceInfo const&	namespace_,
															 kodgen::MacroCodeGenEnv&		env,
															 std::string&					inout_result)				noexcept;

		/**
		*	@brief Define the namespace fragment registerer variable for the provided namespace.
		* 
		*	@param namespace_	Target namespace.
		*	@param env			Code generation environment.
		*	@param inout_result	String to append the generated code.
		*/
		void	declareAndDefineNamespaceFragmentRegistererVariable(kodgen::NamespaceInfo const&	namespace_,
																	kodgen::MacroCodeGenEnv&		env,
																	std::string&					inout_result)		noexcept;

		/**
		*	@brief	Recursively declare and define the get namespace fragment function and the namespace registerer variable
		*			for the provided namespace and all its sub namespaces.
		*			Function and registerers are defined in reversed order, so the most inner namespace metadata will be defined first and the most
		*			outer ones at the end.
		*			/!\ This method only generates code when a top-level (without outer entity) namespace is provided.
		*				In all other cases, the method doesn't generate any code. /!\
		*
		*	@param namespace_	Top level namespace.
		*	@param env			Code generation environment.
		*	@param inout_result	String to append the generated code.
		*/
		void	declareAndDefineGetNamespaceFragmentAndRegistererRecursive(kodgen::NamespaceInfo const&	namespace_,
																		   kodgen::MacroCodeGenEnv&		env,
																		   std::string&					inout_result)	noexcept;


		protected:
		virtual ReflectionCodeGenModule*	clone()																		const	noexcept	override;

		virtual bool						initialGenerateHeaderFileHeaderCode(kodgen::MacroCodeGenEnv&		env,
																				std::string&					inout_result)	noexcept	override;

		virtual kodgen::ETraversalBehaviour	generateHeaderFileHeaderCodeForEntity(kodgen::EntityInfo const&	entity,
																				  kodgen::MacroCodeGenEnv&	env,
																				  std::string&				inout_result)		noexcept	override;

		virtual kodgen::ETraversalBehaviour	generateClassFooterCodeForEntity(kodgen::EntityInfo const&	entity,
																			 kodgen::MacroCodeGenEnv&	env,
																			 std::string&				inout_result)			noexcept	override;

		virtual kodgen::ETraversalBehaviour	generateHeaderFileFooterCodeForEntity(kodgen::EntityInfo const&	entity,
																				  kodgen::MacroCodeGenEnv&	env,
																				  std::string&				inout_result)		noexcept	override;

		virtual bool						initialGenerateSourceFileHeaderCode(kodgen::MacroCodeGenEnv&		env,
																				std::string&					inout_result)	noexcept	override;

		virtual kodgen::ETraversalBehaviour	generateSourceFileHeaderCodeForEntity(kodgen::EntityInfo const&	entity,
																				  kodgen::MacroCodeGenEnv&	env,
																				  std::string&				inout_result)		noexcept	override;

		public:
		ReflectionCodeGenModule()								noexcept;
		ReflectionCodeGenModule(ReflectionCodeGenModule const&)	noexcept;
	};

#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.inl"
}