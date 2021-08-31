#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h"

#include "Kodgen/InfoStructures/StructClassInfo.h"

//#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"	//generateNativePropertiesCode

using namespace rfk;

std::hash<std::string> ReflectionCodeGenModule::_stringHasher;

ReflectionCodeGenModule::ReflectionCodeGenModule() noexcept
{
	addPropertyCodeGen(_customInstantiatorProperty);
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

kodgen::ETraversalBehaviour	ReflectionCodeGenModule::generateHeaderFileHeaderCode(kodgen::EntityInfo const* entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (entity == nullptr)
	{
		//Called once at the very beginning of the generation with nullptr entity
		includeHeaderFileHeaders(env, inout_result);
	}
	else
	{
		switch (entity->entityType)
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
				return kodgen::ETraversalBehaviour::Break; 

			case kodgen::EEntityType::Undefined:
				[[fallthrough]];
			default:
				assert(false); //This should never happen
				env.getLogger()->log("The entity " + entity->getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

				return kodgen::ETraversalBehaviour::AbortWithFailure;
		}
	}

	return kodgen::ETraversalBehaviour::Recurse; 
}

kodgen::ETraversalBehaviour	ReflectionCodeGenModule::generateClassFooterCode(kodgen::EntityInfo const* entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	assert(entity != nullptr); //Class footer code should always depend on a non-nullptr entity

	switch (entity->entityType)
	{
		case kodgen::EEntityType::Struct:
			[[fallthrough]];
		case kodgen::EEntityType::Class:
			declareFriendClasses(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
			
			declareClassRegistererField(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
			declareStaticGetArchetypeMethod(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
			declareGetArchetypeMethodIfInheritFromObject(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
			declareAndDefineRegisterChildClassMethod(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);

			return kodgen::ETraversalBehaviour::Recurse;

		case kodgen::EEntityType::Enum:
			return kodgen::ETraversalBehaviour::Continue; //Go to next enum

		case kodgen::EEntityType::Field:
			[[fallthrough]];
		case kodgen::EEntityType::Method:
			return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities
		
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
			env.getLogger()->log("The entity " + entity->getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

			return kodgen::ETraversalBehaviour::AbortWithFailure;
	}
}

kodgen::ETraversalBehaviour ReflectionCodeGenModule::generateHeaderFileFooterCode(kodgen::EntityInfo const* entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (entity == nullptr)
	{
		//Called once at the very beginning of the generation with nullptr entity
	}
	else
	{
		switch (entity->entityType)
		{
			case kodgen::EEntityType::Struct:
				[[fallthrough]];
			case kodgen::EEntityType::Class:
				declareGetArchetypeTemplateSpecialization(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
				
				return kodgen::ETraversalBehaviour::Recurse;

			case kodgen::EEntityType::Enum:
				declareGetEnumTemplateSpecialization(reinterpret_cast<kodgen::EnumInfo const&>(*entity), env, inout_result);
				declareEnumRegistererVariable(reinterpret_cast<kodgen::EnumInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Continue; //Go to next enum

			case kodgen::EEntityType::Variable:
				declareGetVariableFunction(reinterpret_cast<kodgen::VariableInfo const&>(*entity), env, inout_result);
				declareVariableRegistererVariable(reinterpret_cast<kodgen::VariableInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Continue; //Go to next variable

			case kodgen::EEntityType::Function:
				declareGetFunctionFunction(reinterpret_cast<kodgen::FunctionInfo const&>(*entity), env, inout_result);
				declareFunctionRegistererVariable(reinterpret_cast<kodgen::FunctionInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Continue; //Go to next function

			case kodgen::EEntityType::Field:
				[[fallthrough]];
			case kodgen::EEntityType::Method:
				[[fallthrough]];
			case kodgen::EEntityType::EnumValue:
				return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities

			case kodgen::EEntityType::Namespace:
				declareGetNamespaceFragmentFunction(reinterpret_cast<kodgen::NamespaceInfo const&>(*entity), env, inout_result);
				declareNamespaceFragmentRegistererVariable(reinterpret_cast<kodgen::NamespaceInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Recurse;

			case kodgen::EEntityType::Undefined:
				[[fallthrough]];
			default:
				assert(false); //This should never happen
				env.getLogger()->log("The entity " + entity->getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

				return kodgen::ETraversalBehaviour::AbortWithFailure;
		}
	}

	return kodgen::ETraversalBehaviour::Recurse;
}

kodgen::ETraversalBehaviour ReflectionCodeGenModule::generateSourceFileHeaderCode(kodgen::EntityInfo const* entity, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (entity == nullptr)
	{
		//Called once at the very beginning of the generation with nullptr entity
		includeSourceFileHeaders(env, inout_result);
	}
	else
	{
		switch (entity->entityType)
		{
			case kodgen::EEntityType::Struct:
				[[fallthrough]];
			case kodgen::EEntityType::Class:
				defineClassRegistererField(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
				defineStaticGetArchetypeMethod(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
				defineGetArchetypeMethodIfInheritFromObject(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
				defineGetArchetypeTemplateSpecialization(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Recurse;

			case kodgen::EEntityType::Enum:
				defineGetEnumTemplateSpecialization(reinterpret_cast<kodgen::EnumInfo const&>(*entity), env, inout_result);
				defineEnumRegistererVariable(reinterpret_cast<kodgen::EnumInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Continue; //Go to next enum

			case kodgen::EEntityType::Variable:
				defineGetVariableFunction(reinterpret_cast<kodgen::VariableInfo const&>(*entity), env, inout_result);
				defineVariableRegistererVariable(reinterpret_cast<kodgen::VariableInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Continue; //Go to next variable

			case kodgen::EEntityType::Function:
				defineGetFunctionFunction(reinterpret_cast<kodgen::FunctionInfo const&>(*entity), env, inout_result);
				defineFunctionRegistererVariable(reinterpret_cast<kodgen::FunctionInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Continue; //Go to next function

			case kodgen::EEntityType::Field:
				[[fallthrough]];
			case kodgen::EEntityType::Method:
				[[fallthrough]];
			case kodgen::EEntityType::EnumValue:
				return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities

			case kodgen::EEntityType::Namespace:
				defineGetNamespaceFragmentFunction(reinterpret_cast<kodgen::NamespaceInfo const&>(*entity), env, inout_result);
				defineNamespaceFragmentRegistererVariableRecursive(reinterpret_cast<kodgen::NamespaceInfo const&>(*entity), env, inout_result);

				return kodgen::ETraversalBehaviour::Recurse;

			case kodgen::EEntityType::Undefined:
				[[fallthrough]];

			default:
				assert(false); //This should never happen
				env.getLogger()->log("The entity " + entity->getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);

				return kodgen::ETraversalBehaviour::AbortWithFailure;
		}
	}

	return kodgen::ETraversalBehaviour::Recurse;
}

void ReflectionCodeGenModule::includeHeaderFileHeaders(kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "#include <cstddef>" + env.getSeparator() + env.getSeparator() +	//cstddef contains the offsetof macro
					"#include <Refureku/Misc/DisableWarningMacros.h>" + env.getSeparator() + 
					"#include <Refureku/Utility/CodeGenerationHelpers.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/Class.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>" + env.getSeparator() +
		//TODO: Might move some of these includes in the cpp file instead
					"#include <Refureku/TypeInfo/Namespaces/Namespace.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>" + env.getSeparator();
}

void ReflectionCodeGenModule::includeSourceFileHeaders(kodgen::MacroCodeGenEnv& /*env*/, std::string& /*inout_result*/) const noexcept
{
	//None for now
}

void ReflectionCodeGenModule::declareFriendClasses(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "friend rfk::Struct;" + env.getSeparator();
	inout_result += "friend rfk::CodeGenerationHelpers;" + env.getSeparator();
	inout_result += "friend implements_template1__rfk_registerChildClass<" + structClass.name + ", void, void(rfk::Struct&)>; " + env.getSeparator();
}

void ReflectionCodeGenModule::declareStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "public: static ";
	inout_result += (structClass.entityType == kodgen::EEntityType::Struct) ? "rfk::Struct" : "rfk::Class";
	inout_result += " const& staticGetArchetype() noexcept;" + env.getSeparator();
}

void ReflectionCodeGenModule::declareGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		inout_result += "public: virtual ";
		inout_result += (structClass.entityType == kodgen::EEntityType::Struct) ? "rfk::Struct" : "rfk::Class";
		inout_result += " const& getArchetype() const noexcept override;" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineStaticGetArchetypeMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	std::string returnType = (structClass.entityType == kodgen::EEntityType::Struct) ? "rfk::Struct" : "rfk::Class";

	inout_result += returnType + " const& " + structClass.type.getCanonicalName() + "::staticGetArchetype() noexcept {" + env.getSeparator() +
						"static bool initialized = false;" + env.getSeparator() +
						"static " + returnType + " type(\"" + structClass.name + "\", " +
											getEntityId(structClass) + ", "
											"sizeof(" + structClass.name + "), " +
											((structClass.entityType == kodgen::EEntityType::Class) ? "true" : "false") +
											");" + env.getSeparator() +
						"if (!initialized) {" + env.getSeparator() +
						"initialized = true;" + env.getSeparator();

	//Inside the if statement, initialize the Struct metadata
	fillEntityProperties(structClass, env, "type.", inout_result);
	fillClassParentsMetadata(structClass, env, "type.", inout_result);
	fillClassFields(structClass, env, "type", inout_result);
	fillClassMethods(structClass, env, "type.", inout_result);
	fillClassNestedArchetypes(structClass, env, "type.", inout_result);

	inout_result += "type.setDefaultInstantiator(&rfk::defaultInstantiator<" + structClass.name + ">);" + env.getSeparator();

	//End of the initialization if statement
	inout_result += "}" + env.getSeparator();
						

	inout_result += "return type; }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::fillEntityProperties(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	auto getPropertyVariableName = [&entity](int propertyIndex) -> std::string
	{
		return "property_" + entity.name + "_" + entity.properties[propertyIndex].name + "_" + std::to_string(propertyIndex) + "_" + std::to_string(_stringHasher(entity.id));
	};

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
		inout_result += generatedEntityVarName + "properties.reserve(" + std::to_string(entity.properties.size()) + ");" + env.getSeparator();

		//Add all properties
		_propertiesCount.clear();
		for (int i = 0; i < entity.properties.size(); i++)
		{
			generatedPropertyVariableName = getPropertyVariableName(i);

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

			//TODO: Insert per property generated code?

			inout_result += generatedEntityVarName + "properties.emplace_back(&" + generatedPropertyVariableName + ");" + env.getSeparator();
		}
	}
}

void ReflectionCodeGenModule::fillClassParentsMetadata(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string const& generatedEntityVarName, std::string& inout_result) noexcept
{
	if (!structClass.parents.empty())
	{
		inout_result += generatedEntityVarName + "directParents.reserve(" + std::to_string(structClass.parents.size()) + ");" + env.getSeparator();

		for (kodgen::StructClassInfo::ParentInfo parent : structClass.parents)
		{
			inout_result += generatedEntityVarName + "addToParents<" + parent.type.getName(true) + 
				">(static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));" + env.getSeparator();
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

	std::string generatedCode;
	std::string currentMethodVariable;
	for (kodgen::MethodInfo const& method : structClass.methods)
	{
		if (method.isStatic)
		{
			inout_result += "staticMethod = " + generatedEntityVarName + "addStaticMethod(\"" + method.name + "\", " +
							 std::to_string(_stringHasher(method.id)) + "u, "
							 "rfk::Type::getType<" + method.returnType.getName() + ">(), "
							 "std::make_unique<rfk::NonMemberFunction<" + method.getPrototype(true) + ">" + ">(static_cast<" + computeFullMethodPointerType(structClass, method) + ">(& " + structClass.name + "::" + method.name + ")), "
							 "static_cast<rfk::EMethodFlags>(" + std::to_string(computeRefurekuMethodFlags(method)) + "));" + env.getSeparator();

			currentMethodVariable = "staticMethod";
		}
		else
		{
			inout_result += "method = " + generatedEntityVarName + "addMethod(\"" + method.name + "\", " +
									std::to_string(_stringHasher(method.id)) + "u, "
									"rfk::Type::getType<" + method.returnType.getName() + ">(), "
									"std::make_unique<rfk::MemberFunction<" + structClass.name + ", " + method.getPrototype(true) + ">" + ">(static_cast<" + computeFullMethodPointerType(structClass, method) + ">(& " + structClass.name + "::" + method.name + ")), "
									"static_cast<rfk::EMethodFlags>(" + std::to_string(computeRefurekuMethodFlags(method)) + "));" + env.getSeparator();

			currentMethodVariable = "method";
		}

		//Setup parameters
		if (!method.parameters.empty())
		{
			//Add all parameters in a single string
			generatedCode = currentMethodVariable + "->parameters.reserve(" + std::to_string(method.parameters.size()) + "); " + currentMethodVariable;

			for (kodgen::FunctionParamInfo const& param : method.parameters)
			{
				generatedCode += "->addParameter(\"" + param.name + "\", rfk::Type::getType<" + param.type.getName() + ">())";
			}

			//Write generated parameters string to file
			inout_result += generatedCode + ";" + env.getSeparator();
		}

		//Add properties after the method has been fully setup
		//Parameters have been added at this point, so properties generated code can safely add additional checks
		if (method.isStatic)
		{
			fillEntityProperties(method, env, "staticMethod->", inout_result);
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
	kodgen::uint64 nestedArchetypesCount = structClass.nestedStructs.size() + structClass.nestedClasses.size() + structClass.nestedEnums.size();

	//No code to generate if there are no nested entities
	if (nestedArchetypesCount == 0u)
	{
		return;
	}

	//Reserve memory for the correct number of nested entities
	inout_result += generatedEntityVarName + "nestedArchetypes.reserve(" + std::to_string(nestedArchetypesCount) + ");";

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
		inout_result += "archetype = " + generatedEntityVarName + "addNestedArchetype(rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">(), "
								"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedEnum.accessSpecifier)) + "));" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineGetArchetypeMethodIfInheritFromObject(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (env.getFileParsingResult()->structClassTree.isBaseOf("rfk::Object", structClass.getFullName()))
	{
		std::string returnType = (structClass.entityType == kodgen::EEntityType::Struct) ? "rfk::Struct" : "rfk::Class";

		inout_result += std::move(returnType) + " const& " + structClass.type.getCanonicalName() + "::getArchetype() const noexcept { return " + structClass.name + "::staticGetArchetype(); }" + env.getSeparator() + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (structClass.outerEntity == nullptr ||
		structClass.outerEntity->entityType == kodgen::EEntityType::Namespace ||
		(structClass.outerEntity->entityType && (kodgen::EEntityType::Struct | kodgen::EEntityType::Class)) && reinterpret_cast<kodgen::NestedStructClassInfo const&>(structClass).accessSpecifier == kodgen::EAccessSpecifier::Public)
	{
		inout_result += "namespace rfk { template <> rfk::Archetype const* getArchetype<" + structClass.getFullName() + ">() noexcept; }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Generate the getArchetype specialization only if the class is non-nested, namespace nested or publicly nested in a struct/class
	if (structClass.outerEntity == nullptr ||
		structClass.outerEntity->entityType == kodgen::EEntityType::Namespace ||
		(structClass.outerEntity->entityType && (kodgen::EEntityType::Struct | kodgen::EEntityType::Class)) && reinterpret_cast<kodgen::NestedStructClassInfo const&>(structClass).accessSpecifier == kodgen::EAccessSpecifier::Public)
	{
		inout_result += "template <> rfk::Archetype const* rfk::getArchetype<" + structClass.getFullName() + ">() noexcept { " +
			"return &" + structClass.getFullName() + "::staticGetArchetype(); }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareAndDefineRegisterChildClassMethod(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {" + env.getSeparator();

	//Propagate the child class registration to parent classes too
	for (kodgen::StructClassInfo::ParentInfo const& parent : structClass.parents)
	{
		inout_result += "rfk::CodeGenerationHelpers::registerChildClass<" + parent.type.getName(true) + ", ChildClass>(childClass);" + env.getSeparator();
	}

	inout_result += "rfk::Struct const& thisClass = staticGetArchetype();" + env.getSeparator();
	
	//Register the child to the children list
	inout_result += "if constexpr (!std::is_same_v<ChildClass, " + structClass.name + ">) const_cast<rfk::Struct&>(thisClass).children.insert(&childClass);" + env.getSeparator();

	//Make the child class inherit from the parents class fields
	if (!structClass.fields.empty())
	{
		inout_result += "[[maybe_unused]] rfk::Field* field = nullptr; [[maybe_unused]] rfk::StaticField* staticField = nullptr;" + env.getSeparator();
		inout_result += "__RFK_DISABLE_WARNING_PUSH __RFK_DISABLE_WARNING_OFFSETOF " + env.getSeparator();	//Disable offsetof usage warnings

		//Iterate over fields
		std::string properties;
		std::string currentFieldVariable;
		for (kodgen::FieldInfo const& field : structClass.fields)
		{
			if (field.isStatic)
			{
				inout_result += "staticField = childClass.addStaticField(\"" + field.name + "\", " +
								 std::to_string(_stringHasher(field.id)) + "u, "
								 "rfk::Type::getType<" + field.type.getName() + ">(), "
								 "static_cast<rfk::EFieldFlags>(" + std::to_string(computeRefurekuFieldFlags(field)) + "), "
								 "&thisClass, "
								 "&" + structClass.name + "::" + field.name + ");" + env.getSeparator();

				currentFieldVariable = "staticField->";
			}
			else
			{
				inout_result += "field = childClass.addField(\"" + field.name + "\", " +
								 std::to_string(_stringHasher(field.id)) + "u, "
								 "rfk::Type::getType<" + field.type.getName() + ">(), "
								 "static_cast<rfk::EFieldFlags>(" + std::to_string(computeRefurekuFieldFlags(field)) + "), "
								 "&thisClass, "
								 "offsetof(ChildClass, " + field.name + "));" + env.getSeparator();

				currentFieldVariable = "field->";
			}

			//Add properties
			fillEntityProperties(field, env, currentFieldVariable, inout_result);
		}

		inout_result += "__RFK_DISABLE_WARNING_POP" + env.getSeparator();
	}

	inout_result += env.getSeparator() + "}";
}

void ReflectionCodeGenModule::declareClassRegistererField(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "private: static rfk::ArchetypeRegisterer _rfk_archetypeRegisterer;" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineClassRegistererField(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Define the registrator only when there is no outer entity.
	//If there is an outer entity, it will register its nested entities to the database itself.
	if (structClass.outerEntity == nullptr)
	{
		inout_result += "rfk::ArchetypeRegisterer " + structClass.getFullName() + "::_rfk_archetypeRegisterer = &staticGetArchetype(); " + env.getSeparator();
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
	inout_result += "namespace rfk { template <> rfk::Enum const* getEnum<" + enum_.type.getCanonicalName() + ">() noexcept; }" + env.getSeparator();
}

void ReflectionCodeGenModule::defineGetEnumTemplateSpecialization(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	std::string typeName = enum_.type.getCanonicalName();

	inout_result += "template <> rfk::Enum const* rfk::getEnum<" + typeName + ">() noexcept {" + env.getSeparator() +
					"static bool initialized = false;" + env.getSeparator() +
					"static rfk::Enum type(\"" + enum_.name + "\", " +
										   getEntityId(enum_) + ", "
										   "sizeof(" + typeName + "), "
										   "rfk::Type::getType<" + enum_.underlyingType.getCanonicalName() + ">());" + env.getSeparator();

	//Initialize the enum metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
					"initialized = true;" + env.getSeparator();

	fillEntityProperties(enum_, env, "type.", inout_result);

	if (!enum_.enumValues.empty())
	{
		inout_result += "rfk::EnumValue* enumValue = nullptr;" + env.getSeparator() +
						"type.values.reserve(" + std::to_string(enum_.enumValues.size()) + ");" + env.getSeparator();

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

void ReflectionCodeGenModule::declareEnumRegistererVariable(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (enum_.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { extern rfk::ArchetypeRegisterer registerer" + getEntityId(enum_) + "; }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineEnumRegistererVariable(kodgen::EnumInfo const& enum_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (enum_.outerEntity == nullptr)
	{
		inout_result += "rfk::ArchetypeRegisterer rfk::generated::registerer" + getEntityId(enum_) + " = rfk::getEnum<" + enum_.type.getCanonicalName() + ">();" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::declareGetVariableFunction(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "namespace rfk::generated { rfk::Variable const& " + computeGetVariableFunctionName(variable) + "() noexcept; }" + env.getSeparator();
}

void ReflectionCodeGenModule::defineGetVariableFunction(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "rfk::Variable const& rfk::generated::" + computeGetVariableFunctionName(variable) + "() noexcept {" + env.getSeparator() +
					"static bool initialized = false;" + env.getSeparator() + 
					"static rfk::Variable variable(\"" + variable.name + "\", " +
												   getEntityId(variable) + ", "
												   "rfk::Type::getType<" + variable.type.getCanonicalName() + ">(), "
												   "&" + variable.getFullName() + ", "
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

void ReflectionCodeGenModule::declareVariableRegistererVariable(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (variable.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { extern rfk::DefaultEntityRegisterer variableRegisterer" + getEntityId(variable) + "; }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineVariableRegistererVariable(kodgen::VariableInfo const& variable, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (variable.outerEntity == nullptr)
	{
		inout_result += "rfk::DefaultEntityRegisterer rfk::generated::variableRegisterer" + getEntityId(variable) + " = &rfk::generated::" + computeGetVariableFunctionName(variable) + "();" + env.getSeparator();
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

void ReflectionCodeGenModule::declareGetFunctionFunction(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "namespace rfk::generated { rfk::Function const& " + computeGetFunctionFunctionName(function) + "() noexcept; }" + env.getSeparator();
}

void ReflectionCodeGenModule::defineGetFunctionFunction(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	std::string nonMemberFuncType = "rfk::NonMemberFunction<" + function.getPrototype(true) + ">";

	inout_result += "rfk::Function const& rfk::generated::" + computeGetFunctionFunctionName(function) + "() noexcept {" + env.getSeparator() +
					"static bool initialized = false;" + env.getSeparator() + 
					"static rfk::Function function(\"" + function.name + "\", " +
												   getEntityId(function) + ", "
												   "rfk::Type::getType<" + function.returnType.getCanonicalName() + ">(), "
												   "std::unique_ptr<" + nonMemberFuncType + ">(new " + nonMemberFuncType + "(&" + function.getFullName() + ")), "
													"static_cast<rfk::EFunctionFlags>(" + std::to_string(computeRefurekuFunctionFlags(function)) + ")"
												   ");" + env.getSeparator();

	//Initialize variable metadata
	inout_result += "if (!initialized) {" + env.getSeparator() +
					"initialized = true;" + env.getSeparator();

	fillEntityProperties(function, env, "function.", inout_result);

	//End initialization if
	inout_result += "}";

	inout_result += "return function; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareFunctionRegistererVariable(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (function.outerEntity == nullptr)
	{
		inout_result += "namespace rfk::generated { extern rfk::DefaultEntityRegisterer functionRegisterer" + getEntityId(function) + "; }" + env.getSeparator();
	}
}

void ReflectionCodeGenModule::defineFunctionRegistererVariable(kodgen::FunctionInfo const& function, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	if (function.outerEntity == nullptr)
	{
		inout_result += "rfk::DefaultEntityRegisterer rfk::generated::functionRegisterer" + getEntityId(function) + " = &rfk::generated::" + computeGetFunctionFunctionName(function) + "();" + env.getSeparator();
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



void ReflectionCodeGenModule::declareGetNamespaceFragmentFunction(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += " namespace rfk::generated { "
					"rfk::NamespaceFragment const& " + computeGetNamespaceFragmentFunctionName(namespace_, env.getFileParsingResult()->parsedFile) + "() noexcept;"
					" }" + env.getSeparator();
}

void ReflectionCodeGenModule::defineGetNamespaceFragmentFunction(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "rfk::NamespaceFragment const& rfk::generated::" + computeGetNamespaceFragmentFunctionName(namespace_, env.getFileParsingResult()->parsedFile) + "() noexcept {" + env.getSeparator() +
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
		inout_result += "fragment.nestedEntities.reserve(" + std::to_string(nestedEntityCount) + "u);" + env.getSeparator();

		//Chain fill all nested entities at once
		inout_result += "rfk::NamespaceFragment* fragmentPtr = &fragment;" + env.getSeparator() +
						"fragmentPtr";

		//Nested...
		//Namespaces
		for (kodgen::NamespaceInfo const& nestedNamespace : namespace_.namespaces)
		{
			inout_result += "->addNestedEntity(rfk::generated::" + computeNamespaceFragmentRegistererName(nestedNamespace, env.getFileParsingResult()->parsedFile) + ".getNamespaceInstance())" + env.getSeparator();
		}

		//Structs
		for (kodgen::StructClassInfo const& nestedStruct : namespace_.structs)
		{
			inout_result += "->addNestedEntity(&" + nestedStruct.type.getCanonicalName() + "::staticGetArchetype())" + env.getSeparator();
		}

		//Classes
		for (kodgen::StructClassInfo const& nestedClass : namespace_.classes)
		{
			inout_result += "->addNestedEntity(&" + nestedClass.type.getCanonicalName() + "::staticGetArchetype())" + env.getSeparator();
		}

		//Enums
		for (kodgen::EnumInfo const& nestedEnum : namespace_.enums)
		{
			inout_result += "->addNestedEntity(rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">())" + env.getSeparator();
		}

		//Variables
		for (kodgen::VariableInfo const& variable : namespace_.variables)
		{
			inout_result += "->addNestedEntity(&rfk::generated::" + computeGetVariableFunctionName(variable) + "())" + env.getSeparator();
		}

		//Functions
		for (kodgen::FunctionInfo const& function : namespace_.functions)
		{
			inout_result += "->addNestedEntity(&rfk::generated::" + computeGetFunctionFunctionName(function) + "())" + env.getSeparator();
		}
	}

	//End initialization if
	inout_result += "; }";

	inout_result += "return fragment; }" + env.getSeparator();
}

void ReflectionCodeGenModule::declareNamespaceFragmentRegistererVariable(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "namespace rfk::generated {"
					"extern rfk::NamespaceFragmentRegisterer " + computeNamespaceFragmentRegistererName(namespace_, env.getFileParsingResult()->parsedFile) + ";"
					"}" + env.getSeparator();
}

void ReflectionCodeGenModule::defineNamespaceFragmentRegistererVariableRecursive(kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//Use a lambda since since this portion of code should not be accessible to other methods
	auto const defineNamespaceFragmentRegistererVariable = [](kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result) -> void
	{
		//Nested lambda to make a recursive lambda call
		auto const defineNamespaceFragmentRegistererVariableInternal = [](kodgen::NamespaceInfo const& namespace_, kodgen::MacroCodeGenEnv& env, std::string& inout_result,
																		   auto const& declareNamespaceFragmentRegistererVariableInternalRef) -> void
		{
			for (kodgen::NamespaceInfo const& nestedNamespace : namespace_.namespaces)
			{
				declareNamespaceFragmentRegistererVariableInternalRef(nestedNamespace, env, inout_result, declareNamespaceFragmentRegistererVariableInternalRef);
			}

			inout_result += " rfk::NamespaceFragmentRegisterer rfk::generated::" + computeNamespaceFragmentRegistererName(namespace_, env.getFileParsingResult()->parsedFile) + " = "
							"rfk::NamespaceFragmentRegisterer(\"" + namespace_.name + "\", " +
							getEntityId(namespace_) + ", "
							"&rfk::generated::" + computeGetNamespaceFragmentFunctionName(namespace_, env.getFileParsingResult()->parsedFile) + "(), " +
							((namespace_.outerEntity == nullptr) ? "true" : "false") +
							");" + env.getSeparator();
		};

		defineNamespaceFragmentRegistererVariableInternal(namespace_, env, inout_result, defineNamespaceFragmentRegistererVariableInternal);
	};

	//Generate code only if it is a top-level namespace
	if (namespace_.outerEntity == nullptr)
	{
		defineNamespaceFragmentRegistererVariable(namespace_, env, inout_result);
	}
}

std::string ReflectionCodeGenModule::computeGetNamespaceFragmentFunctionName(kodgen::NamespaceInfo const& namespace_, fs::path const& sourceFile) noexcept
{
	return "getNamespaceFragment" + getEntityId(namespace_) + "_" + std::to_string(_stringHasher(sourceFile.string()));
}

std::string ReflectionCodeGenModule::computeNamespaceFragmentRegistererName(kodgen::NamespaceInfo const& namespace_, fs::path const& sourceFile)	noexcept
{
	return "namespaceFragmentRegisterer" + getEntityId(namespace_) + "_" + std::to_string(_stringHasher(sourceFile.string()));
}

//void FileGenerationUnit::writeHeader(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
//{
//	//Always call base class
//	kodgen::FileGenerationUnit::writeHeader(file, parsingResult);
//
//	file.writeLines("#include <Refureku/Misc/DisableWarningMacros.h>",
//					"#include <Refureku/TypeInfo/Namespaces/Namespace.h>",
//					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>",
//					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>",
//					"#include <Refureku/TypeInfo/Archetypes/Class.h>",
//					"#include <Refureku/TypeInfo/Archetypes/Enum.h>",
//					"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>",
//					"#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>",
//					"\n");
//}
//
//void FileGenerationUnit::generateEndFileMacro(kodgen::GeneratedFile& file) const noexcept
//{
//	file.writeLine("#define " + getEndFileMacroName() + "\t\\");
//
//	//Enum first because structs/classes and namespaces can have nested (and then reference to) enums
//	for (kodgen::EnumInfo const* enumInfo : _generatedEnums)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(enumInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Gen variables
//	for (kodgen::VariableInfo const* varInfo : _generatedVariables)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(varInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Gen functions
//	for (kodgen::FunctionInfo const* funcInfo : _generatedFunctions)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(funcInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Structs/Classes before namespaces because namespaces can have nested (and then reference to) structs/classes
//	for (kodgen::StructClassInfo const* classInfo : _generatedClasses)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(classInfo->id)) + "u_GetTypeDefinition\t\\");
//	}
//
//	for (kodgen::NamespaceInfo const* namespaceInfo : _generatedNamespaces)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(namespaceInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Native properties footer code
//	file.writeLine("	" + _nativePropsMacroName + "\t\\");
//
//	//New line to avoid "warning: backslash-newline at end of file"
//	file.writeLine("\n");
//}
//
//void FileGenerationUnit::saveEntitiesUsingNativeProperties(kodgen::EntityInfo const& entityInfo) noexcept
//{
//	for (kodgen::SimpleProperty const& prop : entityInfo.properties.simpleProperties)
//	{
//		if (prop.boundPropertyRule != nullptr)
//		{
//			_entitiesUsingNativeProperties.push_back(&entityInfo);
//			return;
//		}
//	}
//
//	for (kodgen::ComplexProperty const& prop : entityInfo.properties.complexProperties)
//	{
//		if (prop.boundPropertyRule != nullptr)
//		{
//			_entitiesUsingNativeProperties.push_back(&entityInfo);
//			return;
//		}
//	}
//}
//
//void FileGenerationUnit::generateNativePropertiesCode(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& /* parsingResult */) const noexcept
//{
//	std::string generatedCode;
//
//	//Generate native properties header code
//	PropertyCodeGenFileHeaderData headerData;
//	
//	for (kodgen::EntityInfo const* entityInfo : _entitiesUsingNativeProperties)
//	{
//		assert(entityInfo != nullptr);
//
//		generatedCode += GeneratedEntityCodeTemplate::generateNativePropertiesCode(*entityInfo, &headerData);
//	}
//
//	file.writeLine(generatedCode);
//
//	//Generate native properties footer code inside a macro
//	PropertyCodeGenFileFooterData footerData;
//
//	generatedCode.clear();
//	for (kodgen::EntityInfo const* entityInfo : _entitiesUsingNativeProperties)
//	{
//		assert(entityInfo != nullptr);
//
//		generatedCode += GeneratedEntityCodeTemplate::generateNativePropertiesCode(*entityInfo, &footerData);
//	}
//
//	file.writeMacro(std::string(_nativePropsMacroName), std::move(generatedCode));
//}