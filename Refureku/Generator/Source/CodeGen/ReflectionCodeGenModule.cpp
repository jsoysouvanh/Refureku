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
				break;

			case kodgen::EEntityType::Enum:
				return kodgen::ETraversalBehaviour::Continue; //Go to next enum

			case kodgen::EEntityType::Variable:
				[[fallthrough]];
			case kodgen::EEntityType::Function:
				break;

			case kodgen::EEntityType::Field:
				[[fallthrough]];
			case kodgen::EEntityType::Method:
				[[fallthrough]];
			case kodgen::EEntityType::EnumValue:
				return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities

			case kodgen::EEntityType::Namespace:
				break;

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
			
			declareStaticGetArchetypeMethod(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
			declareGetArchetypeMethodIfInheritFromObject(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
			declareAndDefineRegisterChildClassMethod(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);

			break;

		case kodgen::EEntityType::Enum:
			return kodgen::ETraversalBehaviour::Continue; //Go to next enum

		case kodgen::EEntityType::Variable:
			[[fallthrough]];
		case kodgen::EEntityType::Function:
			break;

		case kodgen::EEntityType::Field:
			[[fallthrough]];
		case kodgen::EEntityType::Method:
			[[fallthrough]];
		case kodgen::EEntityType::EnumValue:
			return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities

		case kodgen::EEntityType::Namespace:
			break;

		case kodgen::EEntityType::Undefined:
			[[fallthrough]];

		default:
			assert(false); //This should never happen
			env.getLogger()->log("The entity " + entity->getFullName() + " has an undefined type. Abort.", kodgen::ILogger::ELogSeverity::Error);
			return kodgen::ETraversalBehaviour::AbortWithFailure;
	}

	return kodgen::ETraversalBehaviour::Recurse;
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
				break;

			case kodgen::EEntityType::Enum:
				return kodgen::ETraversalBehaviour::Continue; //Go to next enum

			case kodgen::EEntityType::Variable:
				[[fallthrough]];
			case kodgen::EEntityType::Function:
				break;

			case kodgen::EEntityType::Field:
				[[fallthrough]];
			case kodgen::EEntityType::Method:
				[[fallthrough]];
			case kodgen::EEntityType::EnumValue:
				return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities

			case kodgen::EEntityType::Namespace:
				break;

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
				defineStaticGetArchetypeMethod(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
				defineGetArchetypeMethodIfInheritFromObject(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);
				defineGetArchetypeTemplateSpecialization(reinterpret_cast<kodgen::StructClassInfo const&>(*entity), env, inout_result);

				break;

			case kodgen::EEntityType::Enum:
				return kodgen::ETraversalBehaviour::Continue; //Go to next enum

			case kodgen::EEntityType::Variable:
				[[fallthrough]];
			case kodgen::EEntityType::Function:
				break;

			case kodgen::EEntityType::Field:
				[[fallthrough]];
			case kodgen::EEntityType::Method:
				[[fallthrough]];
			case kodgen::EEntityType::EnumValue:
				return kodgen::ETraversalBehaviour::Break; //Don't need to iterate over those individual entities

			case kodgen::EEntityType::Namespace:
				break;

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
	inout_result += "#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>" + env.getSeparator() +
					"#include <Refureku/TypeInfo/Archetypes/Class.h>" + env.getSeparator() +
					"#include <Refureku/Utility/CodeGenerationHelpers.h>" + env.getSeparator();
}

void ReflectionCodeGenModule::includeSourceFileHeaders(kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	//TODO: Can improve this by only including used header files depending on the parsing result for this file.
	//inout_result += "#include <Refureku/TypeInfo/Archetypes/Class.h>" + env.getSeparator();

	inout_result += env.getSeparator();

	//inout_result += "#include <Refureku/Misc/DisableWarningMacros.h>\n"
	//				"#include <Refureku/TypeInfo/Namespaces/Namespace.h>\n"
	//				"#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>\n"
	//				"#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>\n"
	//				"#include <Refureku/TypeInfo/Archetypes/Class.h>\n"
	//				"#include <Refureku/TypeInfo/Archetypes/Enum.h>\n"
	//				"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>\n"
	//				"#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>\n";
}

void ReflectionCodeGenModule::declareFriendClasses(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) const noexcept
{
	inout_result += "friend rfk::Struct;" + env.getSeparator();
	inout_result += "friend rfk::CodeGenerationHelpers;" + env.getSeparator();
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

	//End of the initialization if statement
	inout_result += "}" + env.getSeparator();
						

	inout_result += "return type; }" + env.getSeparator() + env.getSeparator();
}

void ReflectionCodeGenModule::fillEntityProperties(kodgen::EntityInfo const& entity, kodgen::MacroCodeGenEnv& env, std::string&& generatedEntityVarName, std::string& inout_result) noexcept
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

void ReflectionCodeGenModule::fillClassParentsMetadata(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string&& generatedEntityVarName, std::string& inout_result) noexcept
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

void ReflectionCodeGenModule::fillClassFields(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string&& generatedClassRefExpression, std::string& inout_result) noexcept
{
	inout_result += structClass.name + "::_registerChildClass<" + structClass.name + ">(" + std::forward<std::string>(generatedClassRefExpression) + ");" + env.getSeparator();
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

void ReflectionCodeGenModule::defineGetArchetypeTemplateSpecialization(kodgen::StructClassInfo const& structClass, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
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
	inout_result += "private: template <typename ChildClass> static void _registerChildClass(rfk::Struct& childClass) noexcept {" + env.getSeparator();

	//Propagate the child class registration to parent classes too
	for (kodgen::StructClassInfo::ParentInfo const& parent : structClass.parents)
	{
		inout_result += "rfk::CodeGenerationHelpers::registerChildClass<" + parent.type.getName(true) + ", ChildClass>(childClass); ";
	}

	//Register the child to the children list


	inout_result += "}";
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