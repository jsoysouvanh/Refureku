/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline std::string ReflectionCodeGenModule::getEntityId(kodgen::EntityInfo const& entity) noexcept
{
	return std::to_string(ReflectionCodeGenModule::_stringHasher(entity.id)) + "u";
}

ReflectionCodeGenModule::ReflectionCodeGenModule() noexcept:
	_isGeneratingHiddenCode{false}
{
	addPropertyCodeGen(_instantiatorProperty);
	addPropertyCodeGen(_propertySettingsProperty);
}

ReflectionCodeGenModule::ReflectionCodeGenModule(ReflectionCodeGenModule const&) noexcept:
	ReflectionCodeGenModule()
{
}

ReflectionCodeGenModule* ReflectionCodeGenModule::clone() const noexcept
{
	return new ReflectionCodeGenModule(*this);
}

bool ReflectionCodeGenModule::initialGenerateHeaderFileHeaderCode(kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	reset();

	includeHeaderFileHeaders(env, inout_result);

	return true;
}

kodgen::ETraversalBehaviour	ReflectionCodeGenModule::generateHeaderFileHeaderCodeForEntity(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string& /* inout_result */) noexcept
{
	kodgen::ETraversalBehaviour result = kodgen::ETraversalBehaviour::Recurse;

	switch (entity.entityType)
	{
		case kodgen::EEntityType::Struct:
			[[fallthrough]];
		case kodgen::EEntityType::Class:
			[[fallthrough]];
		case kodgen::EEntityType::Enum:
			[[fallthrough]];
		case kodgen::EEntityType::Variable:
			[[fallthrough]];
		case kodgen::EEntityType::Function:
			[[fallthrough]];
		case kodgen::EEntityType::Field:
			[[fallthrough]];
		case kodgen::EEntityType::Method:
			[[fallthrough]];
		case kodgen::EEntityType::EnumValue:
			[[fallthrough]];
		case kodgen::EEntityType::Namespace:
			result = kodgen::ETraversalBehaviour::Break; 
			break;

		case kodgen::EEntityType::Undefined:
			[[fallthrough]];
		default:
			assert(false); //This should never happen
			env.getLogger()->log("The entity " + entity.getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

			return kodgen::ETraversalBehaviour::AbortWithFailure;
	}

	checkHiddenGeneratedCodeState();

	return result; 
}

kodgen::ETraversalBehaviour	ReflectionCodeGenModule::generateClassFooterCodeForEntity(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	kodgen::ETraversalBehaviour result = kodgen::ETraversalBehaviour::Recurse;

	switch (entity.entityType)
	{
		case kodgen::EEntityType::Struct:
			[[fallthrough]];
		case kodgen::EEntityType::Class:
			//Do not generate code for forward declarations
			if (static_cast<kodgen::StructClassInfo const&>(entity).isForwardDeclaration)
			{
				return kodgen::ETraversalBehaviour::Continue;
			}

			beginHiddenGeneratedCode(env, inout_result);

			declareFriendClasses(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);

			declareAndDefineRegisterChildClassMethod(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);

			if (static_cast<kodgen::StructClassInfo const&>(entity).type.isTemplateType())
			{
				//Declaration AND definition must appear in the class footer for class templates
				declareAndDefineClassTemplateStaticGetArchetypeMethod(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				declareAndDefineClassTemplateGetArchetypeMethodIfInheritFromObject(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				declareAndDefineClassTemplateRegistererField(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
			}
			else
			{
				declareStaticGetArchetypeMethod(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				declareGetArchetypeMethodIfInheritFromObject(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
			}

			endHiddenGeneratedCode(env, inout_result);

			result = kodgen::ETraversalBehaviour::Recurse;
			break;

		case kodgen::EEntityType::Enum:
			result = kodgen::ETraversalBehaviour::Continue; //Go to next enum
			break;

		case kodgen::EEntityType::Field:
			[[fallthrough]];
		case kodgen::EEntityType::Method:
			result = kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities
			break;

			//All those cases should not be able to be called in generateClassFooterCode
		case kodgen::EEntityType::Variable:
			[[fallthrough]];
		case kodgen::EEntityType::Function:
			[[fallthrough]];
		case kodgen::EEntityType::Namespace:
			[[fallthrough]];
		case kodgen::EEntityType::EnumValue:
			[[fallthrough]];
		case kodgen::EEntityType::Undefined:
			[[fallthrough]];
		default:
			assert(false); //This should never happen
			env.getLogger()->log("The entity " + entity.getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

			return kodgen::ETraversalBehaviour::AbortWithFailure;
	}

	checkHiddenGeneratedCodeState();

	return result;
}

kodgen::ETraversalBehaviour ReflectionCodeGenModule::generateHeaderFileFooterCodeForEntity(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	kodgen::ETraversalBehaviour result = kodgen::ETraversalBehaviour::Recurse;

	switch (entity.entityType)
	{
		case kodgen::EEntityType::Struct:
			[[fallthrough]];
		case kodgen::EEntityType::Class:
			//Do not generate code for forward declarations
			if (reinterpret_cast<kodgen::StructClassInfo const&>(entity).isForwardDeclaration)
			{
				return kodgen::ETraversalBehaviour::Continue;
			}

			declareGetArchetypeTemplateSpecialization(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Recurse;
			break;

		case kodgen::EEntityType::Enum:
			declareGetEnumTemplateSpecialization(static_cast<kodgen::EnumInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next enum
			break;

		case kodgen::EEntityType::Variable:
			if (static_cast<kodgen::VariableInfo const&>(entity).isStatic)
			{
				defineGetVariableFunction(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);
			}
			else
			{
				declareGetVariableFunction(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);
			}

			result = kodgen::ETraversalBehaviour::Continue; //Go to next variable
			break;

		case kodgen::EEntityType::Function:
			if (static_cast<kodgen::FunctionInfo const&>(entity).isStatic)
			{
				defineGetFunctionFunction(static_cast<kodgen::FunctionInfo const&>(entity), env, inout_result);
			}
			else
			{
				declareGetFunctionFunction(static_cast<kodgen::FunctionInfo const&>(entity), env, inout_result);
			}

			result = kodgen::ETraversalBehaviour::Continue; //Go to next function
			break;

		case kodgen::EEntityType::Field:
			[[fallthrough]];
		case kodgen::EEntityType::Method:
			[[fallthrough]];
		case kodgen::EEntityType::EnumValue:
			result =  kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities
			break;

		case kodgen::EEntityType::Namespace:
			result = kodgen::ETraversalBehaviour::Recurse;
			break;

		case kodgen::EEntityType::Undefined:
			[[fallthrough]];
		default:
			assert(false); //This should never happen
			env.getLogger()->log("The entity " + entity.getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

			return kodgen::ETraversalBehaviour::AbortWithFailure;
	}

	checkHiddenGeneratedCodeState();

	return result;
}

bool ReflectionCodeGenModule::initialGenerateSourceFileHeaderCode(kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	includeSourceFileHeaders(env, inout_result);

	return true;
}

kodgen::ETraversalBehaviour ReflectionCodeGenModule::generateSourceFileHeaderCodeForEntity(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	kodgen::ETraversalBehaviour result = kodgen::ETraversalBehaviour::Recurse;

	switch (entity.entityType)
	{
		case kodgen::EEntityType::Struct:
			[[fallthrough]];
		case kodgen::EEntityType::Class:
			//Do not generate code for forward declarations
			if (reinterpret_cast<kodgen::StructClassInfo const&>(entity).isForwardDeclaration)
			{
				return kodgen::ETraversalBehaviour::Continue;
			}

			if (static_cast<kodgen::StructClassInfo const&>(entity).type.isTemplateType())
			{
				defineClassTemplateGetArchetypeTemplateSpecialization(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				declareAndDefineClassTemplateRegistererVariable(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
			}
			else
			{
				declareAndDefineClassRegistererVariable(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				defineStaticGetArchetypeMethod(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				defineGetArchetypeMethodIfInheritFromObject(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
				defineGetArchetypeTemplateSpecialization(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
			}

			result = kodgen::ETraversalBehaviour::Recurse;
			break;

		case kodgen::EEntityType::Enum:
			defineGetEnumTemplateSpecialization(static_cast<kodgen::EnumInfo const&>(entity), env, inout_result);
			declareAndDefineEnumRegistererVariable(static_cast<kodgen::EnumInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next enum
			break;

		case kodgen::EEntityType::Variable:
			if (!static_cast<kodgen::VariableInfo const&>(entity).isStatic)
			{
				defineGetVariableFunction(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);
			}

			declareAndDefineVariableRegistererVariable(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next variable
			break;

		case kodgen::EEntityType::Function:
			if (!static_cast<kodgen::FunctionInfo const&>(entity).isStatic)
			{
				defineGetFunctionFunction(static_cast<kodgen::FunctionInfo const&>(entity), env, inout_result);
			}

			declareAndDefineFunctionRegistererVariable(static_cast<kodgen::FunctionInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next function
			break;

		case kodgen::EEntityType::Field:
			[[fallthrough]];
		case kodgen::EEntityType::Method:
			[[fallthrough]];
		case kodgen::EEntityType::EnumValue:
			result = kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities
			break;

		case kodgen::EEntityType::Namespace:
			declareAndDefineGetNamespaceFragmentAndRegistererRecursive(static_cast<kodgen::NamespaceInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Recurse;
			break;

		case kodgen::EEntityType::Undefined:
			[[fallthrough]];

		default:
			assert(false); //This should never happen
			env.getLogger()->log("The entity " + entity.getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

			return kodgen::ETraversalBehaviour::AbortWithFailure;
	}

	checkHiddenGeneratedCodeState();

	return result;
}

void ReflectionCodeGenModule::includeHeaderFileHeaders(kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "#include <string>" + env.getSeparator() +
		"#include <Refureku/Misc/CodeGenerationHelpers.h>" + env.getSeparator() +
		"#include <Refureku/Misc/DisableWarningMacros.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Functions/Method.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Functions/StaticMethod.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Variables/Field.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Variables/StaticField.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Archetypes/Enum.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Archetypes/EnumValue.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Variables/Variable.h>" + env.getSeparator() +											//TODO: Only if there is a variable
		"#include <Refureku/TypeInfo/Functions/Function.h>" + env.getSeparator() +											//TODO: Only if there is a function
		"#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h>" + env.getSeparator() +							//TODO: Only when there is a template class
		"#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h>" + env.getSeparator() +				//TODO: Only when there is a template class
		"#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegisterer.h>" + env.getSeparator() +	//TODO: Only when there is a non-nested template class
		"#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h>" + env.getSeparator() +					//TODO: Only when there is a template class
		"#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h>" + env.getSeparator() +					//TODO: Only when there is a template class
		"#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h>" + env.getSeparator() +				//TODO: Only when there is a template class
		env.getSeparator();
}

void ReflectionCodeGenModule::includeSourceFileHeaders(kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>" + env.getSeparator() +					//TODO: Only if there is a variable or function
		"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>" + env.getSeparator() +
		"#include <Refureku/TypeInfo/Namespace/Namespace.h>" + env.getSeparator() +								//TODO: Only if there is a namespace
		"#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>" + env.getSeparator() +						//TODO: Only if there is a namespace
		"#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>" + env.getSeparator() +			//TODO: Only if there is a namespace
		"#include <Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h>" + env.getSeparator() +		//TODO: Only if there is a template class in the parsed data
		"#include <Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h>" + env.getSeparator() +	//TODO: Only if there is a template class in the parsed data
		"#include <Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h>" + env.getSeparator() +	//TODO: Only if there is a template class in the parsed data
		env.getSeparator();
}

void ReflectionCodeGenModule::declareFriendClasses(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "friend rfk::internal::CodeGenerationHelpers;" + env.getSeparator();
	inout_result += "friend rfk::internal::implements_template1__rfk_registerChildClass<" + structClass.name + ", void, void(rfk::Struct&)>; " + env.getSeparator();

	auto generateFriendStatementsForNestedArchetypes = [&env, &inout_result, &structClass]() -> void
	{
		bool generatedNonTemplateNestedClassGetArchetypeFriendStatement = false;
		bool generatedGetEnumFriendStatement = false;
		bool generatedVariadicTypeTemplateGetArchetype = false;
		bool generatedVariadicNonTypeTemplateGetArchetype = false;

		auto intermediateLambda = [&generatedNonTemplateNestedClassGetArchetypeFriendStatement, &generatedGetEnumFriendStatement,
								   &generatedVariadicTypeTemplateGetArchetype, &generatedVariadicNonTypeTemplateGetArchetype, &env, &inout_result]
								   (kodgen::StructClassInfo const& structClass, auto const& thisLambda, std::size_t nestingLevel) -> void
		{
			auto generateFriendStatementsForNestedArcheteypesInternal = [&generatedNonTemplateNestedClassGetArchetypeFriendStatement, &generatedVariadicTypeTemplateGetArchetype,
																		 &generatedVariadicNonTypeTemplateGetArchetype, &env, &inout_result]
																		 (std::vector<std::shared_ptr<kodgen::NestedStructClassInfo>> const& nestedStructClasses,
																		  auto const& recurseLambda, std::size_t nestingLevel) -> void
			{
				auto classTemplateCodeGeneration = [&generatedVariadicTypeTemplateGetArchetype, &generatedVariadicNonTypeTemplateGetArchetype, &env, &inout_result]
													(std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedStructClass)
				{
					//Case all template params are type template params
					if (std::all_of(nestedStructClass->type.getTemplateParameters().cbegin(),
						nestedStructClass->type.getTemplateParameters().cend(),
						[](kodgen::TemplateParamInfo const& templateParam)
						{
							return templateParam.kind == kodgen::ETemplateParameterKind::TypeTemplateParameter;
						}))
					{
						if (generatedVariadicTypeTemplateGetArchetype)
						{
							return;
						}

						generatedVariadicTypeTemplateGetArchetype = true;
						inout_result += "template <template <typename...> typename>";
					}
					//Case all template params are non-type template params
					else if (std::all_of(nestedStructClass->type.getTemplateParameters().cbegin(),
							 nestedStructClass->type.getTemplateParameters().cend(),
							 [](kodgen::TemplateParamInfo const& templateParam)
							 {
								 return templateParam.kind == kodgen::ETemplateParameterKind::NonTypeTemplateParameter;
							 }))
					{
						if (generatedVariadicNonTypeTemplateGetArchetype)
						{
							return;
						}

						generatedVariadicNonTypeTemplateGetArchetype = true;
						inout_result += "template <template <auto...> typename>";
					}
					//Other cases
					else
					{
						inout_result += "template <template <" + nestedStructClass->type.computeTemplateSignature(true) + "> typename>";
					}

					inout_result += " friend rfk::Archetype const* rfk::getArchetype() noexcept;" + env.getSeparator();

					//Reflect class template nested archetypes is not supported for now, so no recursion from here.
				};

				for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedStructClass : nestedStructClasses)
				{
					if (nestedStructClass->accessSpecifier == kodgen::EAccessSpecifier::Public && nestingLevel == 1u)
					{
						//If the first nesting level is public, then it is normally accessible, no friend statement needed
						continue;
					}
					else if (nestedStructClass->type.isTemplateType())
					{
						classTemplateCodeGeneration(nestedStructClass);
					}
					else //Non-public non-template class
					{
						//If the basic definition for all non-template classes has not been generated yet, generate it
						if (!generatedNonTemplateNestedClassGetArchetypeFriendStatement)
						{
							generatedNonTemplateNestedClassGetArchetypeFriendStatement = true;
							inout_result += "template <typename> friend rfk::Archetype const* rfk::getArchetype() noexcept;" + env.getSeparator();
						}

						recurseLambda(*nestedStructClass, recurseLambda, nestingLevel + 1u);
					}
				}
			};

			generateFriendStatementsForNestedArcheteypesInternal(structClass.nestedStructs, thisLambda, nestingLevel);
			generateFriendStatementsForNestedArcheteypesInternal(structClass.nestedClasses, thisLambda, nestingLevel);

			//Generate rfk::getEnum friend statement if necessary
			if (!generatedGetEnumFriendStatement)
			{
				for (kodgen::NestedEnumInfo const& nestedEnum : structClass.nestedEnums)
				{
					if (nestingLevel != 1u || nestedEnum.accessSpecifier != kodgen::EAccessSpecifier::Public)
					{
						generatedGetEnumFriendStatement = true;
						inout_result += "template <typename> friend rfk::Enum const* rfk::getEnum() noexcept;" + env.getSeparator();
						break;
					}
				}
			}
		};

		intermediateLambda(structClass, intermediateLambda, 1u);
	};

	generateFriendStatementsForNestedArchetypes();

	inout_result += env.getSeparator();
}

void ReflectionCodeGenModule::declareStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "public: ";
	
	//This is injected inside the class, so don't redeclare export symbol if the class already declares it (because it causes compil errors on MSVC)
	if (!structClass.isImportExport)
	{
		inout_result += env.getExportSymbolMacro();
	}
	
	inout_result += " static ";
	inout_result += (structClass.isClass()) ? "rfk::Class" : "rfk::Struct";
	inout_result += " const& staticGetArchetype() noexcept;" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		inout_result += "public: ";

		//This is injected inside the class, so don't redeclare export symbol if the class already declares it (because it causes compil errors on MSVC)
		if (!structClass.isImportExport)
		{
			inout_result += env.getExportSymbolMacro();
		}

		inout_result += " virtual ";
		inout_result += (structClass.isClass()) ? "rfk::Class" : "rfk::Struct";
		inout_result += " const& getArchetype() const noexcept override;" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	std::string returnType = (structClass.isClass()) ? "rfk::Class" : "rfk::Struct";

	inout_result += returnType + " const& " + structClass.type.getCanonicalName() + "::staticGetArchetype() noexcept {" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator() +
		"static " + returnType + " type(\"" + structClass.name + "\", " +
		getEntityId(structClass) + ", "
		"sizeof(" + structClass.name + "), " +
		std::to_string(structClass.isClass()) +
		");" + env.getSeparator() +
		"if (!initialized) {" + env.getSeparator() +
		"initialized = true;" + env.getSeparator();

	//Inside the if statement, initialize the Struct metadata
	fillEntityProperties(structClass, env, "type.", inout_result);
	fillClassParents(structClass, env, "type.", inout_result);
	fillClassFields(structClass, env, "type", inout_result);

	//Set the default instantiator BEFORE filling the class methods since methods can overwrite the custom instantiator
	setClassDefaultInstantiators(structClass, env, "type.", inout_result);
	fillClassMethods(structClass, env, "type.", inout_result);
	fillClassNestedArchetypes(structClass, env, "type.", inout_result);

	//End of the initialization if statement
	inout_result += "}" + env.getSeparator();


	inout_result += "return type; }" + env.getSeparator() + env.getSeparator();
}

std::string ReflectionCodeGenModule::computePropertyVariableName(kodgen::EntityInfo const& entity, kodgen::uint8 propertyIndex) noexcept
{
	return "property_" + getEntityId(entity) + "_" + std::to_string(propertyIndex);
}

bool ReflectionCodeGenModule::isPublicClass(kodgen::StructClassInfo const& class_) noexcept
{
	if (class_.outerEntity == nullptr)
	{
		return true;
	}
	else
	{
		//class outer entity can only be a namespace or another struct/class
		if (class_.outerEntity->entityType == kodgen::EEntityType::Namespace)
		{
			//Namespace can't be private
			return true;
		}
		else
		{
			//A class outer entity must be another struct or class
			assert(class_.outerEntity->entityType && (kodgen::EEntityType::Class | kodgen::EEntityType::Struct));

			return	static_cast<kodgen::NestedStructClassInfo const&>(class_).accessSpecifier == kodgen::EAccessSpecifier::Public &&
				isPublicClass(static_cast<kodgen::StructClassInfo const&>(*class_.outerEntity));
		}
	}
}

std::string ReflectionCodeGenModule::computeClassTemplateEntityId(kodgen::StructClassInfo const& class_, kodgen::EntityInfo const& entity) noexcept
{
	return computeClassNestedEntityId(class_.getFullName(), entity);
}

std::string ReflectionCodeGenModule::computeClassNestedEntityId(std::string className, kodgen::EntityInfo const& entity) noexcept
{
	return "std::hash<std::string>()(std::string(\"" + entity.id + "\") + rfk::internal::getTypename<" + std::move(className) + ">())";
}

std::string ReflectionCodeGenModule::computeGetArchetypeFunctionSignature(kodgen::StructClassInfo const& structClass) noexcept
{
	return "rfk::Archetype const* rfk::getArchetype<" + structClass.type.getName() + ">() noexcept";
}

void ReflectionCodeGenModule::beginHiddenGeneratedCode(kodgen::MacroCodeGenEnv& /*env*/, std::string& inout_result) noexcept
{
	if (!_isGeneratingHiddenCode)
	{
		_isGeneratingHiddenCode = true;
		inout_result += "RFK_UNPACK_IF_NOT_PARSING(";
	}
}

void ReflectionCodeGenModule::endHiddenGeneratedCode(kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (_isGeneratingHiddenCode)
	{
		_isGeneratingHiddenCode = false;
		inout_result += ")" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::reset() noexcept
{
	_isGeneratingHiddenCode = false;
}

void ReflectionCodeGenModule::checkHiddenGeneratedCodeState() const noexcept
{
	assert(!_isGeneratingHiddenCode);
}

void ReflectionCodeGenModule::fillEntityProperties(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	auto generatePropertyStaticAsserts = [this, &entity](kodgen::Property const& property) -> std::string
	{
		std::string result;

		//Generate AllowMultiple assert only if a property apprears for the second time
		auto it = _propertiesCount.find(property.name);

		if (it != _propertiesCount.end())
		{
			if (it->second == 1)
			{
				//Second apparition of the property, generate
				result += "static_assert(" + property.name + "::allowMultiple, \"[Refureku] " + entity.getFullName() + ": " + property.name + " can't be attached multiple times to a single entity.\"); ";
			}

			++it->second;
		}
		else
		{
			_propertiesCount[property.name] = 1;
		}

		//Generate entity kind check
		std::string entityKindName = convertEntityTypeToEntityKind(entity.entityType);
		result += "static_assert((" + property.name + "::targetEntityKind & " + entityKindName + ") != " + convertEntityTypeToEntityKind(kodgen::EEntityType::Undefined) +
			", \"[Refureku] " + property.name + " can't be applied to a " + entityKindName + "\");";

		return result;
	};

	std::string generatedPropertyVariableName;

	if (!entity.properties.empty())
	{
		//Reserve space to avoid reallocation
		inout_result += generatedEntityVarName + "setPropertiesCapacity(" + std::to_string(entity.properties.size()) + ");" + env.getSeparator();

		//Add all properties
		_propertiesCount.clear();
		for (kodgen::uint8 i = 0; i < entity.properties.size(); i++)
		{
			generatedPropertyVariableName = computePropertyVariableName(entity, i);

			//Generate static_asserts bound to this property
			inout_result += generatePropertyStaticAsserts(entity.properties[i]);

			//Declare property
			inout_result += "static " + entity.properties[i].name + " " + generatedPropertyVariableName;

			//Construct the property with the provided arguments
			if (!entity.properties[i].arguments.empty())
			{
				inout_result += "{";

				for (std::string const& argument : entity.properties[i].arguments)
				{
					inout_result += argument + ",";
				}

				inout_result.back() = '}';	//Replace the last , by a }
			}

			inout_result.push_back(';');

			inout_result += generatedEntityVarName + "addProperty(" + generatedPropertyVariableName + ");" + env.getSeparator();
		}
	}
}

void ReflectionCodeGenModule::setClassDefaultInstantiators(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env,
														  std::string const& generatedClassVarName, std::string& inout_result) noexcept
{
	inout_result += "static rfk::StaticMethod defaultSharedInstantiator(\"\", 0u, rfk::getType<rfk::SharedPtr<" + structClass.name +">>(),"
		"new rfk::NonMemberFunction<rfk::SharedPtr<" + structClass.name + ">()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<" + structClass.name + ">),"
		"rfk::EMethodFlags::Default, nullptr);" + env.getSeparator();

	inout_result += generatedClassVarName + "addSharedInstantiator(defaultSharedInstantiator);" + env.getSeparator();

	inout_result += "static rfk::StaticMethod defaultUniqueInstantiator(\"\", 0u, rfk::getType<rfk::UniquePtr<" + structClass.name +">>(),"
		"new rfk::NonMemberFunction<rfk::UniquePtr<" + structClass.name + ">()>(&rfk::internal::CodeGenerationHelpers::defaultUniqueInstantiator<" + structClass.name + ">),"
		"rfk::EMethodFlags::Default, nullptr);" + env.getSeparator();

	inout_result += generatedClassVarName + "addUniqueInstantiator(defaultUniqueInstantiator);" + env.getSeparator();
}

void ReflectionCodeGenModule::fillClassParents(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env,
											   std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	if (!structClass.parents.empty())
	{
		inout_result += generatedEntityVarName + "setDirectParentsCapacity(" + std::to_string(structClass.parents.size()) + ");" + env.getSeparator();

		for (kodgen::StructClassInfo::ParentInfo const& parent : structClass.parents)
		{
			inout_result += generatedEntityVarName + "addDirectParent("
				"rfk::getArchetype<" + parent.type.getName(true) + ">(), "
				"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));" + env.getSeparator();
		}
	}
}

void ReflectionCodeGenModule::fillClassFields(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string generatedClassRefExpression, std::string& inout_result) noexcept
{
	inout_result += structClass.name + "::_rfk_registerChildClass<" + structClass.name + ">(" + std::move(generatedClassRefExpression) + ");" + env.getSeparator();
}

void ReflectionCodeGenModule::fillClassMethods(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	if (!structClass.methods.empty())
	{
		inout_result += "[[maybe_unused]] rfk::Method* method = nullptr; [[maybe_unused]] rfk::StaticMethod* staticMethod = nullptr;" + env.getSeparator();
	}

	std::size_t setMethodsCountInsertionOffset = inout_result.size();
	std::size_t methodsCount = 0u;
	std::size_t staticMethodsCount = 0u;

	std::string generatedCode;
	std::string currentMethodVariable;
	for (kodgen::MethodInfo const& method : structClass.methods)
	{
		if (method.isStatic)
		{
			staticMethodsCount++;

			inout_result += "staticMethod = " + generatedEntityVarName + "addStaticMethod(\"" + method.name + "\", " +
				(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, method) : std::to_string(_stringHasher(method.id)) + "u") + ", "
				"rfk::getType<" + method.returnType.getName() + ">(), "
				"new rfk::NonMemberFunction<" + method.getPrototype(true) + ">(& " + structClass.name + "::" + method.name + "), "
				"static_cast<rfk::EMethodFlags>(" + std::to_string(computeRefurekuMethodFlags(method)) + "));" + env.getSeparator();

			currentMethodVariable = "staticMethod";
		}
		else
		{
			methodsCount++;

			inout_result += "method = " + generatedEntityVarName + "addMethod(\"" + method.name + "\", " +
				(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, method) : std::to_string(_stringHasher(method.id)) + "u") + ", "
				"rfk::getType<" + method.returnType.getName() + ">(), "
				"new rfk::MemberFunction<" + structClass.name + ", " + method.getPrototype(true) + ">(static_cast<" + computeFullMethodPointerType(structClass, method) + ">(& " + structClass.name + "::" + method.name + ")), "
				"static_cast<rfk::EMethodFlags>(" + std::to_string(computeRefurekuMethodFlags(method)) + "));" + env.getSeparator();

			currentMethodVariable = "method";
		}

		//Setup parameters
		if (!method.parameters.empty())
		{
			//Add all parameters in a single string
			generatedCode = currentMethodVariable + "->setParametersCapacity(" + std::to_string(method.parameters.size()) + "); " + env.getSeparator();

			for (kodgen::FunctionParamInfo const& param : method.parameters)
			{
				generatedCode += currentMethodVariable + "->addParameter(\"" + param.name + "\", 0u, rfk::getType<" + param.type.getName() + ">());" + env.getSeparator();	//TODO: Build Id for parameters
			}

			//Write generated parameters string to file
			inout_result += generatedCode + env.getSeparator();
		}

		//Add properties after the method has been fully setup
		//Parameters have been added at this point, so properties generated code can safely add additional checks
		if (method.isStatic)
		{
			fillEntityProperties(method, env, "staticMethod->", inout_result);

			//Generate specific code for the Instantiator property here
			for (kodgen::uint8 i = 0; i < method.properties.size(); i++)
			{
				if (_instantiatorProperty.shouldGenerateCodeForEntity(method, method.properties[i], i))
				{
					_instantiatorProperty.addInstantiatorToClass(method, method.properties[i], generatedEntityVarName, "staticMethod", inout_result);
					break;
				}
			}
		}
		else
		{
			fillEntityProperties(method, env, "method->", inout_result);

			//Base method properties must be inherited AFTER this method properties have been added
			if (method.isOverride)
			{
				inout_result += "method->inheritBaseMethodProperties();" + env.getSeparator();
			}
		}
	}

	//Generate code to reserve right amount of memory for methods and static methods
	std::string setMethodsCapacityGeneratedCode = generatedEntityVarName + "setMethodsCapacity(" + std::to_string(methodsCount) + "u); ";
	inout_result.insert(setMethodsCountInsertionOffset, setMethodsCapacityGeneratedCode); //methods
	inout_result.insert(setMethodsCountInsertionOffset + setMethodsCapacityGeneratedCode.size(),
						generatedEntityVarName + "setStaticMethodsCapacity(" + std::to_string(staticMethodsCount) + "u); " + env.getSeparator()); //static methods
}

void ReflectionCodeGenModule::fillClassNestedArchetypes(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	std::size_t nestedArchetypesCount = structClass.nestedStructs.size() + structClass.nestedClasses.size() + structClass.nestedEnums.size();

	//No code to generate if there are no nested entities
	if (nestedArchetypesCount == 0u)
	{
		return;
	}

	//Reserve memory for the correct number of nested entities
	inout_result += generatedEntityVarName + "setNestedArchetypesCapacity(" + std::to_string(nestedArchetypesCount) + ");" + env.getSeparator();

	auto addNestedStructClassLambda = [&inout_result, &generatedEntityVarName, &env](std::shared_ptr<kodgen::NestedStructClassInfo> const& structClass)
	{
		inout_result += generatedEntityVarName + "addNestedArchetype(rfk::getArchetype<" + structClass->type.getCanonicalName() + ">(), "
			"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(structClass->accessSpecifier)) + "));" + env.getSeparator();
	};

	//Add nested structs
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedStruct : structClass.nestedStructs)
	{
		addNestedStructClassLambda(nestedStruct);
	}

	//Add nested classes
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedClass : structClass.nestedClasses)
	{
		addNestedStructClassLambda(nestedClass);
	}

	//Add nested enums
	for (kodgen::NestedEnumInfo const& nestedEnum : structClass.nestedEnums)
	{
		inout_result += generatedEntityVarName + "addNestedArchetype(" + 
			"rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">(), "
			"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedEnum.accessSpecifier)) + "));" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		std::string returnType = (structClass.isClass()) ? "rfk::Class" : "rfk::Struct";

		inout_result += std::move(returnType) + " const& " + structClass.type.getCanonicalName() + "::getArchetype() const noexcept { return " + structClass.name + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "template <> " + env.getExportSymbolMacro() + " " + computeGetArchetypeFunctionSignature(structClass) + ";" + env.getSeparator();
}

void ReflectionCodeGenModule::defineGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "template <> rfk::Archetype const* rfk::getArchetype<" + structClass.getFullName() + ">() noexcept { " +
		"return &" + structClass.getFullName() + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineRegisterChildClassMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	bool isGeneratingHiddenCode = _isGeneratingHiddenCode;

	inout_result += "private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {" + env.getSeparator();

	inout_result += "rfk::Struct const& thisClass = staticGetArchetype();" + env.getSeparator();

	//Register the child to the subclasses list
	inout_result += "if constexpr (!std::is_same_v<ChildClass, " + structClass.name + ">)"
		"const_cast<rfk::Struct&>(thisClass).addSubclass(childClass, rfk::internal::CodeGenerationHelpers::computeClassPointerOffset<ChildClass, " + structClass.name + ">());" + env.getSeparator();
	inout_result += "else" + env.getSeparator() + 
		"{" + env.getSeparator();

	//Insert code here to reserve the correct amount of memory for fields and static fields
	//The code is generated at the end of this method
	std::size_t setFieldsCountInsertionOffset = inout_result.size();
	std::size_t fieldsCount = 0u;
	std::size_t staticFieldsCount = 0u;

	inout_result += "}" + env.getSeparator();

	//Make the child class inherit from the parents class fields
	if (!structClass.fields.empty())
	{
		inout_result += "[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;" + env.getSeparator();

		//Trick to have the pragma statement outside of the UNPACK_IF_NOT_PARSING macro
		//If not doing that, the pragma is ignored and offsetof warnings are issued on gcc & clang.
		if (isGeneratingHiddenCode)
		{
			endHiddenGeneratedCode(env, inout_result);
			inout_result += "__RFK_DISABLE_WARNING_PUSH " + env.getSeparator() + "__RFK_DISABLE_WARNING_OFFSETOF " + env.getSeparator();	//Disable offsetof usage warnings
			beginHiddenGeneratedCode(env, inout_result);
		}
		else
		{
			inout_result += "__RFK_DISABLE_WARNING_PUSH " + env.getSeparator() + "__RFK_DISABLE_WARNING_OFFSETOF " + env.getSeparator();	//Disable offsetof usage warnings
		}

		//Iterate over fields
		std::string properties;
		std::string currentFieldVariable;
		for (kodgen::FieldInfo const& field : structClass.fields)
		{
			if (field.isStatic)
			{
				staticFieldsCount++;

				inout_result += "staticField = childClass.addStaticField(\"" + field.name + "\", " +
					(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, field) : computeClassNestedEntityId("ChildClass", field)) + ", " +
					"\"" + field.type.getCanonicalName(true) + "\", " +
					"rfk::getType<" + field.type.getName() + ">(), "
					"static_cast<rfk::EFieldFlags>(" + std::to_string(computeRefurekuFieldFlags(field)) + "), "
					"&" + structClass.name + "::" + field.name + ", "
					"&thisClass);" + env.getSeparator();

				currentFieldVariable = "staticField->";
			}
			else
			{
				fieldsCount++;

				inout_result += "field = childClass.addField(\"" + field.name + "\", " +
					(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, field) : computeClassNestedEntityId("ChildClass", field)) + ", " +
					"\"" + field.type.getCanonicalName(true) + "\", " +
					"rfk::getType<" + field.type.getName() + ">(), "
					"static_cast<rfk::EFieldFlags>(" + std::to_string(computeRefurekuFieldFlags(field)) + "), "
					"offsetof(ChildClass, " + field.name + "), "
					"&thisClass);" + env.getSeparator();

				currentFieldVariable = "field->";
			}

			//Add properties
			fillEntityProperties(field, env, currentFieldVariable, inout_result);
		}

		//Trick to have the pragma statement outside of the UNPACK_IF_NOT_PARSING macro
		//If not doing that, the pragma is ignored and offsetof warnings are issued on gcc & clang.
		if (isGeneratingHiddenCode)
		{
			endHiddenGeneratedCode(env, inout_result);
			inout_result += "__RFK_DISABLE_WARNING_POP " + env.getSeparator();
			beginHiddenGeneratedCode(env, inout_result);
		}
		else
		{
			inout_result += "__RFK_DISABLE_WARNING_POP " + env.getSeparator();
		}
	}

	//Propagate the child class registration to parent classes too
	std::string inheritedFieldsCountExpression;
	std::string inheritedStaticFieldsCountExpression;

	if (!structClass.parents.empty())
	{
		for (kodgen::StructClassInfo::ParentInfo const& parent : structClass.parents)
		{
			inheritedFieldsCountExpression += "rfk::internal::CodeGenerationHelpers::getReflectedFieldsCount< " + parent.type.getName(true) + ">()+";
			inheritedStaticFieldsCountExpression += "rfk::internal::CodeGenerationHelpers::getReflectedStaticFieldsCount< " + parent.type.getName(true) + ">()+";

			inout_result += "rfk::internal::CodeGenerationHelpers::registerChildClass<" + parent.type.getName(true) + ", ChildClass>(childClass);" + env.getSeparator();
		}

		//Remove last + character
		inheritedFieldsCountExpression.pop_back();
		inheritedStaticFieldsCountExpression.pop_back();
	}
	else
	{
		inheritedFieldsCountExpression = "0";
		inheritedStaticFieldsCountExpression = "0";
	}

	//Generate code to reserve right amount of memory for fields and static fields
	std::string setFieldsCapacityGeneratedCode = "childClass.setFieldsCapacity(" + std::to_string(fieldsCount) + "u + " + inheritedFieldsCountExpression + "); ";
	inout_result.insert(setFieldsCountInsertionOffset, setFieldsCapacityGeneratedCode); //fields
	inout_result.insert(setFieldsCountInsertionOffset + setFieldsCapacityGeneratedCode.size(),
						"childClass.setStaticFieldsCapacity(" + std::to_string(staticFieldsCount) + "u + " + inheritedStaticFieldsCountExpression + "); " + env.getSeparator()); //static fields
	
	inout_result += "}" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineClassRegistererVariable(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::ArchetypeRegisterer const registerer_" + getEntityId(structClass) + " = " +
			structClass.getFullName() + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "public: static rfk::ClassTemplateInstantiation const& staticGetArchetype() noexcept {" + env.getSeparator();
	inout_result += "static bool initialized = false;" + env.getSeparator();
	inout_result += "static rfk::ClassTemplateInstantiation type(\"" + structClass.type.getName(false, true) + "\"," +
		computeClassTemplateEntityId(structClass, structClass) + ", " +
		"sizeof(" + structClass.getFullName() + "), " + 
		std::to_string(structClass.isClass()) + ", "
		"*rfk::getArchetype<::" + structClass.type.getName() + ">());" + env.getSeparator();

	//Init content
	inout_result += "if (!initialized) {" + env.getSeparator();
	inout_result += "initialized = true;" + env.getSeparator();

	//Inside the if statement, initialize the Struct metadata
	fillClassTemplateArguments(structClass, "type.", env, inout_result);
	fillEntityProperties(structClass, env, "type.", inout_result);
	fillClassParents(structClass, env, "type.", inout_result);
	fillClassFields(structClass, env, "type", inout_result);

	//Set the default instantiator BEFORE filling the class methods since methods can overwrite the custom instantiator
	setClassDefaultInstantiators(structClass, env, "type.", inout_result);
	fillClassMethods(structClass, env, "type.", inout_result);
	fillClassNestedArchetypes(structClass, env, "type.", inout_result);

	//End init
	inout_result += "}" + env.getSeparator();

	inout_result += "return type; }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		inout_result += "virtual rfk::ClassTemplateInstantiation const& getArchetype() const noexcept override { return staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateRegistererField(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "private: static inline rfk::ClassTemplateInstantiationRegisterer const _rfk_registerer = staticGetArchetype(); rfk::internal::ForceGenerateSymbol<&_rfk_registerer> _rfk_forceRegister() = delete;" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::fillClassTemplateArguments(kodgen::StructClassInfo const& structClass, std::string generatedEntityVarName, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	std::vector<kodgen::TemplateParamInfo> const& templateParameters = structClass.type.getTemplateParameters();
	std::string boundParameterIndex;
	std::string argVarName;

	for (std::size_t i = 0; i < templateParameters.size(); i++)
	{
		boundParameterIndex = std::to_string(i);
		argVarName = "arg" + boundParameterIndex;

		//TODO: this doesn't support auto
		switch (templateParameters[i].kind)
		{
			case kodgen::ETemplateParameterKind::TypeTemplateParameter:
				inout_result += "static rfk::TypeTemplateArgument " + argVarName + "(rfk::getType<" + templateParameters[i].name + ">());" + env.getSeparator();
				break;

			case kodgen::ETemplateParameterKind::NonTypeTemplateParameter:
				inout_result += "static constexpr auto const " + argVarName + "Value = " + templateParameters[i].name + ";" + env.getSeparator();
				inout_result += "static rfk::NonTypeTemplateArgument " + argVarName + "(rfk::getArchetype<decltype(" + templateParameters[i].name + ")>(), "
					"&" + argVarName + "Value);" + env.getSeparator();
				break;

			case kodgen::ETemplateParameterKind::TemplateTemplateParameter:
				inout_result += "static rfk::TemplateTemplateArgument " + argVarName + "(reinterpret_cast<rfk::ClassTemplate const*>(rfk::getArchetype<" + templateParameters[i].name + ">()));" + env.getSeparator();
				break;

			default:
				assert(false);
				break;
		}

		inout_result += "" + generatedEntityVarName + "addTemplateArgument(" + argVarName + ");" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineClassTemplateGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	assert(structClass.type.isTemplateType());

	inout_result += "template <> " + env.getExportSymbolMacro() + " rfk::Archetype const* rfk::getArchetype<" + structClass.type.getName() + ">() noexcept {" + env.getSeparator();
	inout_result += "static bool initialized = false;" + env.getSeparator();
	inout_result += "static rfk::ClassTemplate type(\"" + structClass.type.getName(false, true) + "\", " +
		std::to_string(_stringHasher(structClass.id)) + "u, " +
		std::to_string(structClass.isClass()) + 
		");" + env.getSeparator();

	//Init class template content
	inout_result += "if (!initialized) {" + env.getSeparator();
	inout_result += "initialized = true;" + env.getSeparator();

	fillEntityProperties(structClass, env, "type.", inout_result);

	//Class template has no fields / methods until it is instantiated (no memory address).
	//Likewise, the parent type can depend on the template params which are not accessible from this method, so omit them
	fillClassTemplateParameters(structClass, "type.", env, inout_result);

	//End init if
	inout_result += "}";

	inout_result += "return &type; }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::addTemplateParameter(kodgen::TemplateParamInfo const& templateParam, std::string generatedVarName, std::string const& objVarName,
												   std::string addFuncName, kodgen::MacroCodeGenEnv& env, std::string& inout_result, int recursionLevel) const noexcept
{
	inout_result += "{ " + env.getSeparator();

	switch (templateParam.kind)
	{
		case kodgen::ETemplateParameterKind::NonTypeTemplateParameter:
			//TODO: this does not support auto
			inout_result += "static rfk::NonTypeTemplateParameter " + generatedVarName + "(\"" + templateParam.name + "\", rfk::getArchetype<" + templateParam.type->getName() + ">());" + env.getSeparator();
			break;

		case kodgen::ETemplateParameterKind::TypeTemplateParameter:
			inout_result += "static rfk::TypeTemplateParameter " + generatedVarName + "(\"" + templateParam.name + "\");" + env.getSeparator();
			break;

		case kodgen::ETemplateParameterKind::TemplateTemplateParameter:
			inout_result += "static rfk::TemplateTemplateParameter " + generatedVarName + "(\"" + templateParam.name + "\");" + env.getSeparator();
			for (kodgen::TemplateParamInfo const& param : templateParam.type->getTemplateParameters())
			{
				addTemplateParameter(param, generatedVarName + std::to_string(recursionLevel), generatedVarName + ".", "addTemplateParameter", env, inout_result, recursionLevel + 1);
			}
			break;

		default:
			//Should never reach this point
			assert(false);
	}

	inout_result += objVarName + std::move(addFuncName) + "(" + std::move(generatedVarName) + ");" + env.getSeparator();
	inout_result += "}" + env.getSeparator();
}

void ReflectionCodeGenModule::fillClassTemplateParameters(kodgen::StructClassInfo const& structClass, std::string classTemplateVarName, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	for (kodgen::TemplateParamInfo const& templateParam : structClass.type.getTemplateParameters())
	{
		addTemplateParameter(templateParam, "templateParameter", std::move(classTemplateVarName), "addTemplateParameter", env, inout_result);
	}
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateRegistererVariable(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	assert(structClass.type.isTemplateType());

	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::ArchetypeRegisterer const register_" + getEntityId(structClass) +
			" = *rfk::getArchetype<::" + structClass.type.getName(false, false, true) + ">(); }" + env.getSeparator() + env.getSeparator();
	}
}

std::string ReflectionCodeGenModule::convertEntityTypeToEntityKind(kodgen::EEntityType entityType) noexcept
{
	switch (entityType)
	{
		case kodgen::EEntityType::Struct:
			return "rfk::EEntityKind::Struct";

		case kodgen::EEntityType::Class:
			return "rfk::EEntityKind::Class";

		case kodgen::EEntityType::Enum:
			return "rfk::EEntityKind::Enum";

		case kodgen::EEntityType::EnumValue:
			return "rfk::EEntityKind::EnumValue";

		case kodgen::EEntityType::Field:
			return "rfk::EEntityKind::Field";

		case kodgen::EEntityType::Method:
			return "rfk::EEntityKind::Method";

		case kodgen::EEntityType::Variable:
			return "rfk::EEntityKind::Variable";

		case kodgen::EEntityType::Function:
			return "rfk::EEntityKind::Function";

		case kodgen::EEntityType::Namespace:
			return "rfk::EEntityKind::Namespace";

		case kodgen::EEntityType::Undefined:
			return "rfk::EEntityKind::Undefined";
			break;
	}

	//Should never reach this point
	assert(false);

	return "";
}

kodgen::uint16 ReflectionCodeGenModule::computeRefurekuFieldFlags(kodgen::FieldInfo const& field) noexcept
{
	kodgen::uint16 result = 0;

	switch (field.accessSpecifier)
	{
		case kodgen::EAccessSpecifier::Public:
			result |= 1 << 0;
			break;

		case kodgen::EAccessSpecifier::Protected:
			result |= 1 << 1;
			break;

		case kodgen::EAccessSpecifier::Private:
			result |= 1 << 2;
			break;

		default:
			break;
	}

	if (field.isStatic)
		result |= 1 << 3;

	if (field.isMutable)
		result |= 1 << 4;

	return result;
}

kodgen::uint16 ReflectionCodeGenModule::computeRefurekuMethodFlags(kodgen::MethodInfo const& method) noexcept
{
	kodgen::uint16 result = 0;

	switch (method.accessSpecifier)
	{
		case kodgen::EAccessSpecifier::Public:
			result |= 1 << 0;
			break;

		case kodgen::EAccessSpecifier::Protected:
			result |= 1 << 1;
			break;

		case kodgen::EAccessSpecifier::Private:
			result |= 1 << 2;
			break;

		default:
			break;
	}

	if (method.isStatic)
		result |= 1 << 3;

	if (method.isInline)
		result |= 1 << 4;

	if (method.isVirtual)
		result |= 1 << 5;

	if (method.isPureVirtual)
		result |= 1 << 6;

	if (method.isOverride)
		result |= 1 << 7;

	if (method.isFinal)
		result |= 1 << 8;

	if (method.isConst)
		result |= 1 << 9;

	return result;
}

std::string ReflectionCodeGenModule::computeFullMethodPointerType(kodgen::StructClassInfo const& classInfo, kodgen::MethodInfo const& method) noexcept
{
	std::string result = method.getPrototype();

	if (method.isStatic)
	{
		//Add the ptr on non-member (*) to the type
		result.insert(result.find_first_of('('), "(*)");
	}
	else
	{
		//Add the ptr on member (Class::*) to the type
		result.insert(result.find_first_of('('), "(" + classInfo.name + "::*)");
	}

	return result;
}

void ReflectionCodeGenModule::declareGetEnumTemplateSpecialization(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Don't generate template specialization code on non-public enums
	//Code is generated by the outer class itself
	inout_result += "template <> " + env.getExportSymbolMacro() + " rfk::Enum const* rfk::getEnum<" + enum_.type.getCanonicalName() + ">() noexcept;" + env.getSeparator();
}

void ReflectionCodeGenModule::defineGetEnumTemplateSpecialization(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	//Don't generate template specialization code on non-public enums
	//Code is generated by the outer class itself
	std::string typeName = enum_.type.getCanonicalName();

	inout_result += "template <> rfk::Enum const* rfk::getEnum<" + typeName + ">() noexcept" + env.getSeparator();
	defineGetEnumContent(enum_, env, inout_result);
}

void ReflectionCodeGenModule::defineGetEnumContent(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "{" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator() +
		"static rfk::Enum type(\"" + enum_.name + "\", " +
		getEntityId(enum_) + ", "
		"rfk::getArchetype<" + enum_.underlyingType.getCanonicalName() + ">());" + env.getSeparator();

	//Initialize the enum metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
		"initialized = true;" + env.getSeparator();

	fillEntityProperties(enum_, env, "type.", inout_result);

	if (!enum_.enumValues.empty())
	{
		inout_result += "rfk::EnumValue* enumValue = nullptr;" + env.getSeparator() +
			"type.setEnumValuesCapacity(" + std::to_string(enum_.enumValues.size()) + ");" + env.getSeparator();

		for (kodgen::EnumValueInfo const& enumValue : enum_.enumValues)
		{
			inout_result += "enumValue = type.addEnumValue(\"" + enumValue.name + "\", " + getEntityId(enumValue) + ", " + std::to_string(enumValue.value) + ");" + env.getSeparator();

			//Fill enum value properties
			fillEntityProperties(enumValue, env, "enumValue->", inout_result);
		}
	}

	//End initialization if
	inout_result += "}" + env.getSeparator();


	inout_result += "return &type; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineEnumRegistererVariable(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (enum_.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::ArchetypeRegisterer const registerer_" + getEntityId(enum_) + " = *rfk::getEnum<" + enum_.type.getCanonicalName() + ">(); }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareGetVariableFunction(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	beginHiddenGeneratedCode(env, inout_result);

	inout_result += "template <> " + env.getExportSymbolMacro() + " rfk::Variable const* rfk::getVariable<&" + variable.getFullName() + ">() noexcept; " + env.getSeparator();

	endHiddenGeneratedCode(env, inout_result);
}

void ReflectionCodeGenModule::defineGetVariableFunction(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	std::string fullName = variable.getFullName();

	inout_result += "template <> rfk::Variable const* rfk::getVariable<&" + variable.getFullName() + ">() noexcept {" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator() + 
		"static rfk::Variable variable(\"" + variable.name + "\", " +
		getEntityId(variable) + ", " +
		"\"" + variable.type.getCanonicalName(true) + "\", " + 
		"rfk::getType<decltype(" + fullName + ")>(), "
		"&" + fullName + ", "
		"static_cast<rfk::EVarFlags>(" + std::to_string(computeRefurekuVariableFlags(variable)) + ")"
		");" + env.getSeparator();

	//Initialize variable metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
		"initialized = true;" + env.getSeparator();

	fillEntityProperties(variable, env, "variable.", inout_result);

	//End initialization if
	inout_result += "}";

	inout_result += "return &variable; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineVariableRegistererVariable(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (variable.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::DefaultEntityRegisterer const registerer_" + getEntityId(variable) +
			" = *rfk::getVariable<&" + variable.getFullName() + ">(); }" + env.getSeparator();
	}
}

kodgen::uint8 ReflectionCodeGenModule::computeRefurekuVariableFlags(kodgen::VariableInfo const& variable) noexcept
{
	kodgen::uint8 result = 0u;

	if (variable.isStatic)
	{
		result |= 1 << 0;
	}

	return result;
}

void ReflectionCodeGenModule::declareGetFunctionFunction(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	beginHiddenGeneratedCode(env, inout_result);

	inout_result += "template <> " + env.getExportSymbolMacro() + " rfk::Function const* rfk::getFunction<static_cast<" + computeFunctionPtrType(function) + ">(&" + function.getFullName() + ")>() noexcept; ";

	endHiddenGeneratedCode(env, inout_result);
}

void ReflectionCodeGenModule::defineGetFunctionFunction(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "template <> rfk::Function const* rfk::getFunction<static_cast<" + computeFunctionPtrType(function) + ">(&" + function.getFullName() + ")>() noexcept {" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator() + 
		"static rfk::Function function(\"" + function.name + "\", " +
		getEntityId(function) + ", "
		"rfk::getType<" + function.returnType.getCanonicalName() + ">(), "
		"new rfk::NonMemberFunction<" + function.getPrototype(true) + ">(&" + function.getFullName() + "), "
		"static_cast<rfk::EFunctionFlags>(" + std::to_string(computeRefurekuFunctionFlags(function)) + ")"
		");" + env.getSeparator();

	//Initialize variable metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
		"initialized = true;" + env.getSeparator();

	fillEntityProperties(function, env, "function.", inout_result);

	//Setup parameters
	if (!function.parameters.empty())
	{
		inout_result += "function.setParametersCapacity(" + std::to_string(function.parameters.size()) + ");" + env.getSeparator();

		for (kodgen::FunctionParamInfo const& param : function.parameters)
		{
			inout_result += "function.addParameter(\"" + param.name + "\", 0u, rfk::getType<" + param.type.getName() + ">());" + env.getSeparator();	//TODO: Build an id for the parameter
		}

		inout_result += ";" + env.getSeparator();
	}

	//End initialization if
	inout_result += "}";

	inout_result += "return &function; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineFunctionRegistererVariable(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (function.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::DefaultEntityRegisterer const registerer" + getEntityId(function) +
			" = *rfk::getFunction<static_cast<" + computeFunctionPtrType(function) + ">(&" + function.getFullName() + ")>(); }" + env.getSeparator();
	}
}

kodgen::uint8 ReflectionCodeGenModule::computeRefurekuFunctionFlags(kodgen::FunctionInfo const& function) noexcept
{
	kodgen::uint8 result = 0u;

	if (function.isStatic)
	{
		result |= 1 << 0;
	}

	if (function.isInline)
	{
		result |= 1 << 1;
	}

	return result;
}

std::string ReflectionCodeGenModule::computeFunctionPtrType(kodgen::FunctionInfo const& function) noexcept
{
	return function.returnType.getCanonicalName() + "(*)(" + function.getParameterTypes() + ")";
}

void ReflectionCodeGenModule::declareAndDefineGetNamespaceFragmentFunction(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += env.getInternalSymbolMacro() + " static rfk::NamespaceFragment const& " + computeGetNamespaceFragmentFunctionName(namespace_, env.getFileParsingResult()->parsedFile) + "() noexcept {" + env.getSeparator() +
		"static rfk::NamespaceFragment fragment(\"" + namespace_.name + "\", " + getEntityId(namespace_) + ");" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator();


	//Initialize namespace metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
		"initialized = true;" + env.getSeparator();

	fillEntityProperties(namespace_, env, "fragment.", inout_result);

	size_t nestedEntityCount =	namespace_.namespaces.size() + namespace_.structs.size() + namespace_.classes.size() +
		namespace_.enums.size() + namespace_.variables.size() + namespace_.functions.size();

	if (nestedEntityCount > 0u)
	{
		//Reserve space first
		inout_result += "fragment.setNestedEntitiesCapacity(" + std::to_string(nestedEntityCount) + "u);" + env.getSeparator();

		//Nested...
		//Namespaces
		for (kodgen::NamespaceInfo const& nestedNamespace : namespace_.namespaces)
		{
			inout_result += "fragment.addNestedEntity(rfk::generated::" + computeGetNamespaceFragmentFunctionName(nestedNamespace, env.getFileParsingResult()->parsedFile) + "());" + env.getSeparator();
		}

		//Structs
		for (kodgen::StructClassInfo const& nestedStruct : namespace_.structs)
		{
			inout_result += "fragment.addNestedEntity(*rfk::getArchetype<" + nestedStruct.type.getCanonicalName() + ">());" + env.getSeparator();
		}

		//Classes
		for (kodgen::StructClassInfo const& nestedClass : namespace_.classes)
		{
			inout_result += "fragment.addNestedEntity(*rfk::getArchetype<" + nestedClass.type.getCanonicalName() + ">());" + env.getSeparator();
		}

		//Enums
		for (kodgen::EnumInfo const& nestedEnum : namespace_.enums)
		{
			inout_result += "fragment.addNestedEntity(*rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">());" + env.getSeparator();
		}

		//Variables
		for (kodgen::VariableInfo const& variable : namespace_.variables)
		{
			inout_result += "fragment.addNestedEntity(*rfk::getVariable<&" + variable.getFullName() + ">()); " + env.getSeparator();
		}

		//Functions
		for (kodgen::FunctionInfo const& function : namespace_.functions)
		{
			inout_result += "fragment.addNestedEntity(*rfk::getFunction<static_cast<" + computeFunctionPtrType(function) + ">(&" + function.getFullName() + ")>());" + env.getSeparator();
		}
	}

	//End initialization if
	inout_result += "}" + env.getSeparator();

	inout_result += "return fragment; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineNamespaceFragmentRegistererVariable(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	assert(namespace_.outerEntity == nullptr);

	inout_result += "static rfk::NamespaceFragmentRegisterer const " + computeNamespaceFragmentRegistererName(namespace_, env.getFileParsingResult()->parsedFile) +
		"(rfk::generated::" + computeGetNamespaceFragmentFunctionName(namespace_, env.getFileParsingResult()->parsedFile) + "());" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineGetNamespaceFragmentAndRegistererRecursive(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	//Use a lambda since since this portion of code should not be accessible to other methods
	auto const defineAndDeclareGetNamespaceFragmentAndRegistererLambda = [this](kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) -> void
	{
		//Nested lambda to make a recursive lambda call
		auto const defineAndDeclareGetNamespaceFragmentAndRegistererLambdaInternal = [this](kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result,
																							auto const& defineNamespaceFragmentRegistererVariableInternalRef) -> void
		{
			for (kodgen::NamespaceInfo const& nestedNamespace : namespace_.namespaces)
			{
				defineNamespaceFragmentRegistererVariableInternalRef(nestedNamespace, env, inout_result, defineNamespaceFragmentRegistererVariableInternalRef);
			}

			declareAndDefineGetNamespaceFragmentFunction(namespace_, env, inout_result);
		};

		defineAndDeclareGetNamespaceFragmentAndRegistererLambdaInternal(namespace_, env, inout_result, defineAndDeclareGetNamespaceFragmentAndRegistererLambdaInternal);
	};

	//Generate code only if it is a top-level namespace
	if (namespace_.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { " + env.getSeparator();
		defineAndDeclareGetNamespaceFragmentAndRegistererLambda(namespace_, env, inout_result);
		declareAndDefineNamespaceFragmentRegistererVariable(namespace_, env, inout_result);
		inout_result += " }" + env.getSeparator();
	}
}

std::string ReflectionCodeGenModule::computeGetNamespaceFragmentFunctionName(kodgen::NamespaceInfo const& namespace_, fs::path const& sourceFile) noexcept
{
	return "getNamespaceFragment_" + getEntityId(namespace_) + "_" + std::to_string(_stringHasher(sourceFile.string()));
}

std::string ReflectionCodeGenModule::computeNamespaceFragmentRegistererName(kodgen::NamespaceInfo const& namespace_, fs::path const& sourceFile) noexcept
{
	return "namespaceFragmentRegisterer_" + getEntityId(namespace_) + "_" + std::to_string(_stringHasher(sourceFile.string()));
}