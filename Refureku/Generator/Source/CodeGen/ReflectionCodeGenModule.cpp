#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h"

#include "Kodgen/InfoStructures/StructClassInfo.h"

using namespace rfk;

std::hash<std::string> ReflectionCodeGenModule::_stringHasher;

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
			declareGetNestedEnumMethods(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);

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
			declareGetVariableFunction(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next variable
			break;

		case kodgen::EEntityType::Function:
			declareGetFunctionFunction(static_cast<kodgen::FunctionInfo const&>(entity), env, inout_result);

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
				defineGetNestedEnumMethods(static_cast<kodgen::StructClassInfo const&>(entity), env, inout_result);
			}

			result = kodgen::ETraversalBehaviour::Recurse;
			break;

		case kodgen::EEntityType::Enum:
			defineGetEnumTemplateSpecialization(static_cast<kodgen::EnumInfo const&>(entity), env, inout_result);
			declareAndDefineEnumRegistererVariable(static_cast<kodgen::EnumInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next enum
			break;

		case kodgen::EEntityType::Variable:
			defineGetVariableFunction(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);
			declareAndDefineVariableRegistererVariable(static_cast<kodgen::VariableInfo const&>(entity), env, inout_result);

			result = kodgen::ETraversalBehaviour::Continue; //Go to next variable
			break;

		case kodgen::EEntityType::Function:
			defineGetFunctionFunction(static_cast<kodgen::FunctionInfo const&>(entity), env, inout_result);
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
					"#include <Refureku/Utility/CodeGenerationHelpers.h>" + env.getSeparator() +
					"#include <Refureku/Misc/DisableWarningMacros.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Functions/MethodAPI.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Functions/StaticMethodAPI.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Variables/FieldAPI.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Variables/StaticFieldAPI.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/Enum.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/EnumValue.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateAPI.h>" + env.getSeparator() +							//TODO: Only when there is a template class
					"#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h>" + env.getSeparator() +				//TODO: Only when there is a template class
					"#include <Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererAPI.h>" + env.getSeparator() +		//TODO: Only when there is a non-nested template class
					env.getSeparator();

	//Forward declarations
	inout_result += "namespace rfk { "
					"class VariableAPI; "
					"class FunctionAPI;"
					" }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::includeSourceFileHeaders(kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "#include <Refureku/TypeInfo/Variables/VariableAPI.h>" + env.getSeparator() +						//TODO: Only if there is a variable
					"#include <Refureku/TypeInfo/Functions/FunctionAPI.h>" + env.getSeparator() +						//TODO: Only if there is a function
					"#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Namespace/Namespace.h>" + env.getSeparator() +							//TODO: Only if there is a namespace
					"#include <Refureku/TypeInfo/Namespace/NamespaceFragment.h>" + env.getSeparator() +				//TODO: Only if there is a namespace
					"#include <Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h>" + env.getSeparator() +	//TODO: Only if there is a namespace
					"#include <Refureku/TypeInfo/Archetypes/Template/TemplateParameterAPI.h>" + env.getSeparator() +	//TODO: Only if there is a template class in the parsed data
					 env.getSeparator();
}

void ReflectionCodeGenModule::declareFriendClasses(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "friend rfk::CodeGenerationHelpers;" + env.getSeparator();
	inout_result += "friend implements_template1__rfk_registerChildClass<" + structClass.name + ", void, void(rfk::StructAPI&)>; " + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "public: " + env.getExportSymbolMacro() + " static ";
	inout_result += (structClass.isClass()) ? "rfk::ClassAPI" : "rfk::StructAPI";
	inout_result += " const& staticGetArchetype() noexcept;" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		inout_result += "public: " + env.getExportSymbolMacro() + " virtual ";
		inout_result += (structClass.isClass()) ? "rfk::ClassAPI" : "rfk::StructAPI";
		inout_result += " const& getArchetype() const noexcept override;" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	std::string returnType = (structClass.isClass()) ? "rfk::ClassAPI" : "rfk::StructAPI";

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
	//Set the default instantiator BEFORE filling the class methods since methods can overwrite the custom instantiator
	inout_result += "type.setDefaultInstantiator(&rfk::internal::defaultInstantiator<" + structClass.name + ">);" + env.getSeparator();

	fillEntityProperties(structClass, env, "type.", inout_result);
	fillClassParents(structClass, env, "type.", inout_result);
	fillClassFields(structClass, env, "type", inout_result);
	fillClassMethods(structClass, env, "type.", inout_result);
	fillClassNestedArchetypes(structClass, env, "type.", inout_result);

	//End of the initialization if statement
	inout_result += "}" + env.getSeparator();


	inout_result += "return type; }" + env.getSeparator() + env.getSeparator();
}

std::string ReflectionCodeGenModule::computePropertyVariableName(kodgen::EntityInfo const& entity, kodgen::uint8 propertyIndex) noexcept
{
	return "property_" + getEntityId(entity) + "_" + entity.properties[propertyIndex].name + "_" + std::to_string(propertyIndex);
}

std::string ReflectionCodeGenModule::computeGetNestedEnumMethodName(kodgen::NestedEnumInfo const& nestedEnum) noexcept
{
	return "_rfk_getNestedEnum_" + nestedEnum.name;
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
	return "std::hash<std::string>()(std::string(\"" + entity.id + "\") + rfk::generated::getTypename<" + class_.type.getName() + ">())";
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
	_nonPublicEnums.clear();
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

			inout_result += generatedEntityVarName + "addProperty(&" + generatedPropertyVariableName + ");" + env.getSeparator();
		}
	}
}

void ReflectionCodeGenModule::fillClassParents(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	if (!structClass.parents.empty())
	{
		inout_result += generatedEntityVarName + "setDirectParentsCapacity(" + std::to_string(structClass.parents.size()) + ");" + env.getSeparator();

		for (kodgen::StructClassInfo::ParentInfo parent : structClass.parents)
		{
			if (parent.type.isTemplateType())
			{
				inout_result += generatedEntityVarName + "addDirectParent("
					"rfk::getArchetype<" + parent.type.getName(true, false, true) + ">(), "
					"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));" + env.getSeparator();
			}
			else
			{
				inout_result += generatedEntityVarName + "addDirectParent("
					"rfk::getArchetype<" + parent.type.getName(true) + ">(), "
					"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));" + env.getSeparator();
			}
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
		inout_result += "[[maybe_unused]] rfk::MethodAPI* method = nullptr; [[maybe_unused]] rfk::StaticMethodAPI* staticMethod = nullptr;" + env.getSeparator();
	}

	std::string generatedCode;
	std::string currentMethodVariable;
	for (kodgen::MethodInfo const& method : structClass.methods)
	{
		if (method.isStatic)
		{
			inout_result += "staticMethod = " + generatedEntityVarName + "addStaticMethod(\"" + method.name + "\", " +
				(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, method) : std::to_string(_stringHasher(method.id)) + "u") + ", "
				"rfk::getType<" + method.returnType.getName() + ">(), "
				"new rfk::NonMemberFunction<" + method.getPrototype(true) + ">(& " + structClass.name + "::" + method.name + "), "
				"static_cast<rfk::EMethodFlags>(" + std::to_string(computeRefurekuMethodFlags(method)) + "));" + env.getSeparator();

			currentMethodVariable = "staticMethod";
		}
		else
		{
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
					_instantiatorProperty.addInstantiatorToClass(generatedEntityVarName, "staticMethod", inout_result);
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
	inout_result += generatedEntityVarName + "setNestedArchetypesCapacity(" + std::to_string(nestedArchetypesCount) + ");";

	//Add nested structs
	inout_result += "rfk::Archetype* archetype = nullptr;" + env.getSeparator();
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedStruct : structClass.nestedStructs)
	{
		inout_result += "archetype = " + generatedEntityVarName + "addNestedArchetype(&" + nestedStruct->name + "::staticGetArchetype(), "
			"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedStruct->accessSpecifier)) + "));" + env.getSeparator();
	}

	//Add nested classes
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedClass : structClass.nestedClasses)
	{
		inout_result += "archetype = " + generatedEntityVarName + "addNestedArchetype(&" + nestedClass->name + "::staticGetArchetype(), "
			"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedClass->accessSpecifier)) + "));" + env.getSeparator();
	}

	//Add nested enums
	for (kodgen::NestedEnumInfo const& nestedEnum : structClass.nestedEnums)
	{
		inout_result += "archetype = " + generatedEntityVarName + "addNestedArchetype(" + 
			(isRegisteredNonPublicEnum(nestedEnum) ? computeGetNestedEnumMethodName(nestedEnum) : "rfk::getEnumAPI<" + nestedEnum.type.getCanonicalName() + ">") + "(), "
			"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedEnum.accessSpecifier)) + "));" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		std::string returnType = (structClass.isClass()) ? "rfk::ClassAPI" : "rfk::StructAPI";

		inout_result += std::move(returnType) + " const& " + structClass.type.getCanonicalName() + "::getArchetype() const noexcept { return " + structClass.name + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (isPublicClass(structClass))
	{
		inout_result += "template <> " + env.getExportSymbolMacro() + " rfk::Archetype const* rfk::getArchetype<" + structClass.type.getName() + ">() noexcept;" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Generate the getArchetype specialization only if the class is non-nested, namespace nested or publicly nested in a struct/class
	if (isPublicClass(structClass))
	{
		inout_result += "template <> rfk::Archetype const* rfk::getArchetype<" + structClass.getFullName() + ">() noexcept { " +
			"return &" + structClass.getFullName() + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareAndDefineRegisterChildClassMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	bool isGeneratingHiddenCode = _isGeneratingHiddenCode;

	inout_result += "private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::StructAPI& childClass) noexcept {" + env.getSeparator();

	//Propagate the child class registration to parent classes too
	for (kodgen::StructClassInfo::ParentInfo const& parent : structClass.parents)
	{
		inout_result += "rfk::CodeGenerationHelpers::registerChildClass<" + parent.type.getName(true) + ", ChildClass>(childClass);" + env.getSeparator();
	}

	inout_result += "rfk::StructAPI const& thisClass = staticGetArchetype();" + env.getSeparator();

	//Register the child to the subclasses list
	inout_result += "if constexpr (!std::is_same_v<ChildClass, " + structClass.name + ">) const_cast<rfk::StructAPI&>(thisClass).addSubclass(childClass);" + env.getSeparator();

	//Make the child class inherit from the parents class fields
	if (!structClass.fields.empty())
	{
		inout_result += "[[maybe_unused]] rfk::FieldAPI* field = nullptr; [[maybe_unused]] rfk::StaticFieldAPI* staticField = nullptr;" + env.getSeparator();

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
				inout_result += "staticField = childClass.addStaticField(\"" + field.name + "\", " +
					(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, field) : std::to_string(_stringHasher(field.id)) + "u") + ", " +
					"rfk::getType<" + field.type.getName() + ">(), "
					"static_cast<rfk::EFieldFlags>(" + std::to_string(computeRefurekuFieldFlags(field)) + "), "
					"&" + structClass.name + "::" + field.name + ", "
					"&thisClass);" + env.getSeparator();

				currentFieldVariable = "staticField->";
			}
			else
			{
				inout_result += "field = childClass.addField(\"" + field.name + "\", " +
					(structClass.type.isTemplateType() ? computeClassTemplateEntityId(structClass, field) : std::to_string(_stringHasher(field.id)) + "u") + ", " +
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

	inout_result += "}" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::declareGetNestedEnumMethods(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	bool publicClass = isPublicClass(structClass);

	for (kodgen::NestedEnumInfo const& nestedEnum : structClass.nestedEnums)
	{
		//Generate a method on non-public enums
		//Public nested enums generated code is handled like non-nested enums
		if (!publicClass || nestedEnum.accessSpecifier != kodgen::EAccessSpecifier::Public)
		{
			_nonPublicEnums.emplace(&nestedEnum);

			beginHiddenGeneratedCode(env, inout_result);

			inout_result += "private: static rfk::Enum const* " + computeGetNestedEnumMethodName(nestedEnum) + "() noexcept;" + env.getSeparator();

			endHiddenGeneratedCode(env, inout_result);
		}
	}

	inout_result += env.getSeparator();
}

void ReflectionCodeGenModule::defineGetNestedEnumMethods(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	for (kodgen::NestedEnumInfo const& nestedEnum : structClass.nestedEnums)
	{
		if (isRegisteredNonPublicEnum(nestedEnum))
		{
			inout_result += "rfk::Enum const* " + structClass.getFullName() + "::" + computeGetNestedEnumMethodName(nestedEnum) + "() noexcept" + env.getSeparator();
			defineGetEnumContent(nestedEnum, env, inout_result);
		}
	}
}

void ReflectionCodeGenModule::declareAndDefineClassRegistererVariable(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::ArchetypeRegisterer registerer_" + getEntityId(structClass) + " = " +
			structClass.getFullName() + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "public: static rfk::ClassTemplateInstantiationAPI const& staticGetArchetype() noexcept {" + env.getSeparator();
	inout_result += "static bool initialized = false;" + env.getSeparator();
	inout_result += "static rfk::ClassTemplateInstantiationAPI type(\"" + structClass.type.getName(false, true) + "\"," +
		computeClassTemplateEntityId(structClass, structClass) + ", " +
		"sizeof(" + structClass.type.getName() + "), " + 
		std::to_string(structClass.isClass()) + ", "
		"*rfk::getArchetype<::" + structClass.type.getName() + ">());" + env.getSeparator();

	//Init content
	inout_result += "if (!initialized) {" + env.getSeparator();
	inout_result += "initialized = true;" + env.getSeparator();

	//Inside the if statement, initialize the Struct metadata
	//Set the default instantiator BEFORE filling the class methods since methods can overwrite the custom instantiator
	inout_result += "type.setDefaultInstantiator(&rfk::internal::defaultInstantiator<" + structClass.type.getName() + ">);" + env.getSeparator();

	fillClassTemplateArguments(structClass, env, inout_result);
	fillEntityProperties(structClass, env, "type.", inout_result);
	fillClassParents(structClass, env, "type.", inout_result);
	fillClassFields(structClass, env, "type", inout_result);
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
		inout_result += "virtual rfk::ClassTemplateInstantiationAPI const& getArchetype() const noexcept override { return staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateRegistererField(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "private: static inline rfk::ClassTemplateInstantiationRegistererAPI _rfk_registerer = staticGetArchetype(); rfk::ForceGenerateSymbol<&_rfk_registerer> _rfk_forceRegister() = delete;" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::fillClassTemplateArguments(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	for (std::size_t i = 0; i < structClass.type.getTemplateTypenames().size(); i++)
	{
		inout_result += "type.addTemplateArgument(type.getClassTemplate().getTemplateParameterAt(" + std::to_string(i) + "),"
			"rfk::getArchetype<" + structClass.type.getTemplateTypenames()[i].getName() + ">());" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineClassTemplateGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	assert(structClass.type.isTemplateType());

	inout_result += "template <> " + env.getExportSymbolMacro() + " rfk::Archetype const* rfk::getArchetype<" + structClass.type.getName() + ">() noexcept {" + env.getSeparator();
	inout_result += "static bool initialized = false;" + env.getSeparator();
	inout_result += "static rfk::ClassTemplateAPI type(\"" + structClass.type.getName(false, true) + "\", " +
		std::to_string(_stringHasher(structClass.id)) + "u, " +
		std::to_string(structClass.isClass()) + 
		");" + env.getSeparator();

	//Init class template content
	inout_result += "if (!initialized) {" + env.getSeparator();
	inout_result += "initialized = true;" + env.getSeparator();

	fillEntityProperties(structClass, env, "type.", inout_result);

	//Class template has no fields / methods until it is instantiated (no memory address).
	fillClassParents(structClass, env, "type.", inout_result);
	fillClassTemplateParameters(structClass, env, inout_result);

	//End init if
	inout_result += "}";

	inout_result += "return &type; }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::fillClassTemplateParameters(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	for (kodgen::TypeInfo type : structClass.type.getTemplateTypenames()) //TODO: Replace simple TypeInfo by a more complete TemplateParameter struct
	{
		//TODO: Handle different template parameter types differently

		if (true) //Type template parameter
		{
			inout_result += "{ " + env.getSeparator();
			inout_result += "static rfk::TemplateParameterAPI parameter(\"" + type.getName() + "\", rfk::ETemplateParameterKind::TypeTemplateParameter);" + env.getSeparator();
			inout_result += "type.addTemplateParameter(parameter);" + env.getSeparator();
			inout_result += "}" + env.getSeparator();
		}
		else if (true)	//Template template parameter
		{
			//TODO
		}
		else //Non-type template parameter
		{
			//TODO
		}
	}
}

void ReflectionCodeGenModule::declareAndDefineClassTemplateRegistererVariable(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	assert(structClass.type.isTemplateType());

	inout_result += "namespace rfk::generated { static rfk::ArchetypeRegisterer register_" + getEntityId(structClass) +
		" = *rfk::getArchetype<" + structClass.type.getName(false, false, true) + ">(); }" + env.getSeparator() + env.getSeparator();
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

bool ReflectionCodeGenModule::isRegisteredNonPublicEnum(kodgen::EnumInfo const& nestedEnum) const noexcept
{
	return _nonPublicEnums.find(&nestedEnum) != _nonPublicEnums.cend();
}

void ReflectionCodeGenModule::declareGetEnumTemplateSpecialization(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Don't generate template specialization code on non-public enums
	//Code is generated by the outer class itself
	if (!isRegisteredNonPublicEnum(enum_))
	{
		inout_result += "namespace rfk { template <> " + env.getExportSymbolMacro() + " rfk::Enum const* getEnumAPI<" + enum_.type.getCanonicalName() + ">() noexcept; }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineGetEnumTemplateSpecialization(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	//Don't generate template specialization code on non-public enums
	//Code is generated by the outer class itself
	if (!isRegisteredNonPublicEnum(enum_))
	{
		std::string typeName = enum_.type.getCanonicalName();

		inout_result += "template <> rfk::Enum const* rfk::getEnumAPI<" + typeName + ">() noexcept" + env.getSeparator();
		defineGetEnumContent(enum_, env, inout_result);
	}
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
		inout_result += "namespace rfk::generated { static rfk::ArchetypeRegisterer registerer_" + getEntityId(enum_) + " = *rfk::getEnumAPI<" + enum_.type.getCanonicalName() + ">(); }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareGetVariableFunction(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	beginHiddenGeneratedCode(env, inout_result);

	inout_result += "namespace rfk::generated { rfk::VariableAPI const& " + computeGetVariableFunctionName(variable) + "() noexcept; }" + env.getSeparator();

	endHiddenGeneratedCode(env, inout_result);
}

void ReflectionCodeGenModule::defineGetVariableFunction(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "rfk::VariableAPI const& rfk::generated::" + computeGetVariableFunctionName(variable) + "() noexcept {" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator() + 
		"static rfk::VariableAPI variable(\"" + variable.name + "\", " +
		getEntityId(variable) + ", "
		"rfk::getType<" + variable.type.getCanonicalName() + ">(), "
		"const_cast<" + variable.type.getName(true) + "*>(&" + variable.getFullName() + "), "
		"static_cast<rfk::EVarFlags>(" + std::to_string(computeRefurekuVariableFlags(variable)) + ")"
		");" + env.getSeparator();

	//Initialize variable metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
		"initialized = true;" + env.getSeparator();

	fillEntityProperties(variable, env, "variable.", inout_result);

	//End initialization if
	inout_result += "}";

	inout_result += "return variable; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineVariableRegistererVariable(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (variable.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::DefaultEntityRegisterer registerer_" + getEntityId(variable) +
			" = rfk::generated::" + computeGetVariableFunctionName(variable) + "(); }" + env.getSeparator();
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

std::string ReflectionCodeGenModule::computeGetVariableFunctionName(kodgen::VariableInfo const& variable) noexcept
{
	return "getVariable" + getEntityId(variable);;
}

void ReflectionCodeGenModule::declareGetFunctionFunction(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	beginHiddenGeneratedCode(env, inout_result);

	inout_result += "namespace rfk::generated { rfk::FunctionAPI const& " + computeGetFunctionFunctionName(function) + "() noexcept; }" + env.getSeparator();

	endHiddenGeneratedCode(env, inout_result);
}

void ReflectionCodeGenModule::defineGetFunctionFunction(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "rfk::FunctionAPI const& rfk::generated::" + computeGetFunctionFunctionName(function) + "() noexcept {" + env.getSeparator() +
		"static bool initialized = false;" + env.getSeparator() + 
		"static rfk::FunctionAPI function(\"" + function.name + "\", " +
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

	inout_result += "return function; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineFunctionRegistererVariable(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (function.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { static rfk::DefaultEntityRegisterer registerer" + getEntityId(function) +
			" = rfk::generated::" + computeGetFunctionFunctionName(function) + "(); }" + env.getSeparator();
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

std::string ReflectionCodeGenModule::computeGetFunctionFunctionName(kodgen::FunctionInfo const& function) noexcept
{
	return "getFunction" + getEntityId(function);
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
			inout_result += "fragment.addNestedEntity(rfk::generated::" + computeNamespaceFragmentRegistererName(nestedNamespace, env.getFileParsingResult()->parsedFile) + ".getNamespaceInstance());" + env.getSeparator();
		}

		//Structs
		for (kodgen::StructClassInfo const& nestedStruct : namespace_.structs)
		{
			inout_result += "fragment.addNestedEntity(&" + nestedStruct.type.getCanonicalName() + "::staticGetArchetype());" + env.getSeparator();
		}

		//Classes
		for (kodgen::StructClassInfo const& nestedClass : namespace_.classes)
		{
			inout_result += "fragment.addNestedEntity(&" + nestedClass.type.getCanonicalName() + "::staticGetArchetype());" + env.getSeparator();
		}

		//Enums
		for (kodgen::EnumInfo const& nestedEnum : namespace_.enums)
		{
			inout_result += "fragment.addNestedEntity(rfk::getEnumAPI<" + nestedEnum.type.getCanonicalName() + ">());" + env.getSeparator();
		}

		//Variables
		for (kodgen::VariableInfo const& variable : namespace_.variables)
		{
			inout_result += "fragment.addNestedEntity(&rfk::generated::" + computeGetVariableFunctionName(variable) + "());" + env.getSeparator();
		}

		//Functions
		for (kodgen::FunctionInfo const& function : namespace_.functions)
		{
			inout_result += "fragment.addNestedEntity(&rfk::generated::" + computeGetFunctionFunctionName(function) + "());" + env.getSeparator();
		}
	}

	//End initialization if
	inout_result += "}" + env.getSeparator();

	inout_result += "return fragment; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareAndDefineNamespaceFragmentRegistererVariable(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "static rfk::NamespaceFragmentRegisterer " + computeNamespaceFragmentRegistererName(namespace_, env.getFileParsingResult()->parsedFile) + " = "
		"rfk::NamespaceFragmentRegisterer(\"" + namespace_.name + "\", " +
		getEntityId(namespace_) + ", "
		"rfk::generated::" + computeGetNamespaceFragmentFunctionName(namespace_, env.getFileParsingResult()->parsedFile) + "(), " +
		std::to_string(namespace_.outerEntity == nullptr) +
		");" + env.getSeparator();
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
			declareAndDefineNamespaceFragmentRegistererVariable(namespace_, env, inout_result);
		};

		defineAndDeclareGetNamespaceFragmentAndRegistererLambdaInternal(namespace_, env, inout_result, defineAndDeclareGetNamespaceFragmentAndRegistererLambdaInternal);
	};

	//Generate code only if it is a top-level namespace
	if (namespace_.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { " + env.getSeparator();
		defineAndDeclareGetNamespaceFragmentAndRegistererLambda(namespace_, env, inout_result);
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