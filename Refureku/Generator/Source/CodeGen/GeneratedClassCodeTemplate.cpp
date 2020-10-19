#include "RefurekuGenerator/CodeGen/GeneratedClassCodeTemplate.h"

#include <cassert>
#include <algorithm>

#include <Kodgen/Parsing/FileParserFactoryBase.h>	//For FileParser::parsingMacro
#include <Kodgen/InfoStructures/NestedStructClassInfo.h>
#include <Kodgen/InfoStructures/NestedEnumInfo.h>
#include <Kodgen/Misc/FundamentalTypes.h>

#include "RefurekuGenerator/Properties/NativeProperties.h"
#include "RefurekuGenerator/Misc/Helpers.h"

using namespace rfk;

void GeneratedClassCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo, kodgen::FileGenerationUnit& /* fgu */, std::string& /* out_errorDescription */) const noexcept
{
	switch (entityInfo.entityType)
	{
		case kodgen::EEntityType::Class:
			generateClassCode(generatedFile, static_cast<kodgen::StructClassInfo const&>(entityInfo));
			break;

		case kodgen::EEntityType::Struct:
			generateStructCode(generatedFile, static_cast<kodgen::StructClassInfo const&>(entityInfo));
			break;

		default:
			assert(false);	//Should never reach this point
	}
}

void GeneratedClassCodeTemplate::generateClassCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& classInfo) const noexcept
{
	std::string mainMacroName					= externalPrefix + classInfo.name + "_GENERATED";

	std::string getTypeMacroName				= generateGetArchetypeMacro(generatedFile, classInfo);
	std::string defaultInstantiateMacro			= generateDefaultInstantiateMacro(generatedFile, classInfo);
	std::string generateRegistrationMacroName	= generateRegistrationMacro(generatedFile, classInfo);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParserFactoryBase::parsingMacro);

	generatedFile.writeMacro(std::string(mainMacroName));

	generatedFile.writeLine("#else");

	generatedFile.writeMacro(std::move(mainMacroName),
							 "friend rfk::Struct;",
							 "friend rfk::hasField___rfkArchetypeRegisterer<" + classInfo.name + ", rfk::ArchetypeRegisterer>;",
							 std::move(defaultInstantiateMacro),
							 std::move(getTypeMacroName),
							 std::move(generateRegistrationMacroName),
							 "private:");

	generatedFile.writeLine("#endif\n");
}

void GeneratedClassCodeTemplate::generateStructCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& structInfo) const noexcept
{
	generateClassCode(generatedFile, structInfo);
}

std::string GeneratedClassCodeTemplate::generateGetArchetypeMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string					entityId								= getEntityId(info);
	std::string					getTypeMacroDeclaration					= internalPrefix + entityId + "_GetTypeDeclaration";
	std::string					getTypeMacroDefinition					= internalPrefix + entityId + "_GetTypeDefinition";
	std::string					generateParentsMetadataMacroName		= generateParentsMetadataMacro(generatedFile, info);
	std::array<std::string, 2>	generateFieldsMetadataMacroName			= generateFieldsMetadataMacros(generatedFile, info);
	std::string					generateMethodsMetadataMacroName		= generateMethodsMetadataMacro(generatedFile, info);
	std::string					generateArchetypePropertiesMacroName	= generateArchetypePropertiesMacro(generatedFile, info);
	std::string					generatedNestedClassesMetadataMacroName	= generateNestedArchetypesMetadataMacro(generatedFile, info);

	std::string returnedType = (info.entityType == kodgen::EEntityType::Struct) ? "rfk::Struct" : "rfk::Class";
	
	if (info.isObject)
		std::cout << "Generate: " << "	" + returnedType + " const& getArchetype() const noexcept override { return " + info.name + "::staticGetArchetype(); }" << std::endl;

	generatedFile.writeMacro(std::string(getTypeMacroDeclaration),
							 std::move(generateFieldsMetadataMacroName[1]),
							 "public:",
							 "	inline static " + returnedType + " const& staticGetArchetype() noexcept;",
							 (info.isObject) ? "	" + returnedType + " const& getArchetype() const noexcept override { return " + info.name + "::staticGetArchetype(); }" : ""
	);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParserFactoryBase::parsingMacro);

	generatedFile.writeMacro(std::string(getTypeMacroDefinition));

	generatedFile.writeLine("#else");

	generatedFile.writeMacro(std::move(getTypeMacroDefinition),
								"	inline " + returnedType + " const& " + info.type.getCanonicalName() + "::staticGetArchetype() noexcept",
								"	{",
								"		static bool			initialized = false;",
								"		static " + returnedType + "	type(\"" + info.name + "\", "
																		+ getEntityId(info) + ", "
																		+ "sizeof(" + info.name + "));",
								"	",
								"		if (!initialized)",
								"		{",
								"			initialized = true;",
								"	",
								"			" + std::move(generateArchetypePropertiesMacroName),
								"			" + std::move(generateParentsMetadataMacroName),
								"			" + std::move(generatedNestedClassesMetadataMacroName),
								"			" + std::move(generateFieldsMetadataMacroName[0]),
								"			" + std::move(generateMethodsMetadataMacroName),
								"		}",
								"	",
								"		return type;",
								"	}"
							 );

	generatedFile.writeLine("#endif");

	return getTypeMacroDeclaration;
}

std::string GeneratedClassCodeTemplate::generateArchetypePropertiesMacro(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateArchetypeProperties";

	generatedFile.writeMacro(std::string(macroName), fillEntityProperties(info, "type."));

	return macroName;
}

std::string GeneratedClassCodeTemplate::generateMethodsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateMethodsMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	if (!info.methods.empty())
	{
		generatedFile.writeLine("	std::unordered_multiset<rfk::Method, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator			methodsIt;\t\\");
		generatedFile.writeLine("	std::unordered_multiset<rfk::StaticMethod, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator	staticMethodsIt;\t\\");
		generatedFile.writeLine("	rfk::MethodBase*																						currMethod = nullptr;\t\\");
	}

	std::string properties;
	for (kodgen::MethodInfo const& method : info.methods)
	{
		if (method.isStatic)
		{
			generatedFile.writeLine("	staticMethodsIt = type.staticMethods.emplace(\"" + method.name + "\", " +
									std::to_string(stringHasher(method.id)) + "u, "
									"rfk::Type::getType<" + method.returnType.getName() + ">(), "
									"std::make_unique<rfk::NonMemberFunction<" + method.getPrototype(true) + ">" + ">(static_cast<" + getFullMethodPrototype(info, method) + ">(& " + info.name + "::" + method.name + ")), "
									"static_cast<rfk::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) + "));\t\\");

			//Check if this static method is a custom instantiator, in which case we should add it to the list of custom instantiators of this class
			if (std::find_if(method.properties.simpleProperties.cbegin(), method.properties.simpleProperties.cend(), [](kodgen::SimpleProperty const& sp){ return sp.mainProperty == NativeProperties::customInstantiatorProperty; })
					!= method.properties.simpleProperties.cend())
			{
				generatedFile.writeLine("	type.__RFKaddCustomInstantiator<" + method.returnType.getCanonicalName() + ">(&*staticMethodsIt);\t\\");
			}

			generatedFile.writeLine("	currMethod = const_cast<rfk::StaticMethod*>(&*staticMethodsIt);\t\\");
		}
		else
		{
			generatedFile.writeLine("	methodsIt = type.methods.emplace(\"" + method.name + "\", " +
									std::to_string(stringHasher(method.id)) + "u, "
									"rfk::Type::getType<" + method.returnType.getName() + ">(), "
									"std::make_unique<rfk::MemberFunction<" + info.name + ", " + method.getPrototype(true) + ">" + ">(static_cast<" + getFullMethodPrototype(info, method) + ">(& " + info.name + "::" + method.name + ")), "
									"static_cast<rfk::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) + "));\t\\");

			generatedFile.writeLine("	currMethod = const_cast<rfk::Method*>(&*methodsIt);\t\\");
		}

		//Add properties
		properties = fillEntityProperties(method, "currMethod->");
		if (!properties.empty())
			generatedFile.writeLine("	" + properties + "\t\\");

		//Setup the outer entity
		generatedFile.writeLine("	currMethod->outerEntity = &type;\t\\");

		//Setup parameters
		if (!method.parameters.empty())
		{
			generatedFile.writeLine("	currMethod->parameters.reserve(" + std::to_string(method.parameters.size()) + ");\t\\");

			for (kodgen::FunctionParamInfo const& param : method.parameters)
			{
				generatedFile.writeLine("	currMethod->parameters.emplace_back(\"" + param.name + "\", rfk::Type::getType<" + param.type.getName() + ">());\t\\");
			}
		}
	}

	//Add required methods (instantiate....)
	generatedFile.writeLine("	type.__RFKaddRequiredMethods<" + info.name + ">();\t\\");

	generatedFile.writeLine("");

	return macroName;
}

std::array<std::string, 2> GeneratedClassCodeTemplate::generateFieldsMetadataMacros(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::array<std::string, 2> macroNames = { internalPrefix + getEntityId(info) + "_GenerateFieldsMetadata" };

	generatedFile.writeLine("#define " + macroNames[0] + "\t\\");

	generatedFile.writeLine("	__RFKregisterChild<" + info.name + ">(&type);\t\\");
	generatedFile.writeLine("");

	//Wrap this part in a method so that children classes can use it too
	macroNames[1] = generateFieldHelperMethodsMacro(generatedFile, info);

	return macroNames;
}

std::string GeneratedClassCodeTemplate::generateFieldHelperMethodsMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateFieldHelperMethods";

	//Generate parent registering templated method to discard calls on non reflected parents
	generatedFile.writeLines("#define " + macroName + "\t\\",
							"private:\t\\",
							 "	template <typename ParentType, typename ChildType>\t\\",
							 "	static constexpr void __RFKrecurseRegisterChild([[maybe_unused]] rfk::Struct* childArchetype)\t\\",
							 "	{\t\\",
							 "		if constexpr (rfk::isReflectedClass<ParentType>)\t\\",
							 "		{\t\\",
							 "			ParentType::template __RFKregisterChild<ChildType>(childArchetype);\t\\",
							 "		}\t\\",
							 "	}\t\\",
							 "public:\t\\",
							 "	template <typename ChildType>\t\\",
							 "	static void __RFKregisterChild(rfk::Struct* childArchetype) noexcept\t\\",
							 "	{\t\\");

	for (kodgen::StructClassInfo::ParentInfo const& parent : info.parents)
	{
		generatedFile.writeLine("		__RFKrecurseRegisterChild<" + parent.type.getName(true) + ", ChildType>(childArchetype);\t\\");
	}

	//Add a child to list of children
	generatedFile.writeLines("		rfk::Struct const& thisArchetype = staticGetArchetype();\t\\",
							 "		if (childArchetype != &thisArchetype)\t\\",
							 "		{\t\\",
							 "			const_cast<rfk::Struct&>(thisArchetype).children.insert(childArchetype);\t\\",
							 "		}\t\\");

	bool hasFields = !info.fields.empty();

	if (hasFields)
	{
		generatedFile.writeLine("		std::unordered_multiset<rfk::Field, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator			fieldsIt;\t\\");
		generatedFile.writeLine("		std::unordered_multiset<rfk::StaticField, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator	staticFieldsIt;\t\\");
		generatedFile.writeLine("		rfk::FieldBase*																							currField = nullptr;\t\\");
		generatedFile.writeLines("		__RFK_DISABLE_WARNING_PUSH\t\\",
								 "		__RFK_DISABLE_WARNING_OFFSETOF\t\\");
	}

	std::string properties;
	for (kodgen::FieldInfo const& field : info.fields)
	{
		if (field.isStatic)
		{
			generatedFile.writeLine("		staticFieldsIt = childArchetype->staticFields.emplace(\"" + field.name + "\", " +
											std::to_string(stringHasher(field.id)) + "u, "
											"rfk::Type::getType<" + field.type.getName() + ">(), "
											"static_cast<rfk::EFieldFlags>(" + std::to_string(computeFieldFlags(field)) + "), "
											"childArchetype, "
											"&" + info.name + "::" + field.name + ");\t\\");

			generatedFile.writeLine("		currField = const_cast<rfk::StaticField*>(&*staticFieldsIt);\t\\");
		}
		else
		{
			generatedFile.writeLine("		fieldsIt = childArchetype->fields.emplace(\"" + field.name + "\", " +
											std::to_string(stringHasher(field.id)) + "u, "
											"rfk::Type::getType<" + field.type.getName() + ">(), "
											"static_cast<rfk::EFieldFlags>(" + std::to_string(computeFieldFlags(field)) + "), "
											"childArchetype, "
											"offsetof(ChildType, " + field.name + "));\t\\");

			generatedFile.writeLine("		currField = const_cast<rfk::Field*>(&*fieldsIt);\t\\");
		}

		//Add properties
		properties = fillEntityProperties(field, "	currField->");
		if (!properties.empty())
			generatedFile.writeLine("	" + properties + "\t\\");

		//Setup the outer entity
		generatedFile.writeLine("		currField->outerEntity = &thisArchetype;\t\\");
	}

	if (hasFields)
	{
		generatedFile.writeLine("		__RFK_DISABLE_WARNING_POP\t\\");
	}

	generatedFile.writeLine("	}");
	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedClassCodeTemplate::generateParentsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	if (!info.parents.empty())
	{
		std::string macroName = internalPrefix + getEntityId(info) + "_GenerateParentsMetadata";

		generatedFile.writeLine("#define " + macroName + "\t\\");

		generatedFile.writeLine("	type.directParents.reserve(" + std::to_string(info.parents.size()) + ");\t\\");

		for (kodgen::StructClassInfo::ParentInfo parent : info.parents)
		{
			generatedFile.writeLine("	type.__RFKaddToParents<" + parent.type.getName(true) + ">(static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));\t\\");
		}

		generatedFile.writeLine("");

		return macroName;
	}
	
	//No parents, don't bother generate a macro
	return std::string();
}

std::string GeneratedClassCodeTemplate::generateNestedArchetypesMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	kodgen::uint64 nestedArchetypesCount = info.nestedStructs.size() + info.nestedClasses.size() + info.nestedEnums.size();

	if (nestedArchetypesCount == 0u)
	{
		//No nested archetypes, don't bother generate a macro
		return std::string();
	}

	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateNestedArchetypesMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	generatedFile.writeLine("	std::pair<decltype(type.nestedArchetypes)::iterator, bool> it;\t\\");

	//Reserve memory first
	generatedFile.writeLine("	type.nestedArchetypes.reserve(" + std::to_string(nestedArchetypesCount) + ");\t\\");
	
	//Add nested structs
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedStruct : info.nestedStructs)
	{
		generatedFile.writeLine("	it = type.nestedArchetypes.emplace(&" + nestedStruct->name + "::staticGetArchetype());\t\\");
		generatedFile.writeLine("	const_cast<rfk::Archetype*>((*it.first))->accessSpecifier = static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedStruct->accessSpecifier)) + ");\t\\");
		generatedFile.writeLine("	const_cast<rfk::Archetype*>((*it.first))->outerEntity = &type;\t\\");
	}

	//Add nested classes
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedClass : info.nestedClasses)
	{
		generatedFile.writeLine("	it = type.nestedArchetypes.emplace(&" + nestedClass->name + "::staticGetArchetype());\t\\");
		generatedFile.writeLine("	const_cast<rfk::Archetype*>((*it.first))->accessSpecifier = static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedClass->accessSpecifier)) + ");\t\\");
		generatedFile.writeLine("	const_cast<rfk::Archetype*>((*it.first))->outerEntity = &type;\t\\");
	}

	//Add nested enums
	for (kodgen::NestedEnumInfo const& nestedEnum : info.nestedEnums)
	{
		generatedFile.writeLine("	it = type.nestedArchetypes.emplace(rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">());\t\\");
		generatedFile.writeLine("	const_cast<rfk::Archetype*>((*it.first))->accessSpecifier = static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedEnum.accessSpecifier)) + ");\t\\");
		generatedFile.writeLine("	const_cast<rfk::Archetype*>((*it.first))->outerEntity = &type;\t\\");
	}

	generatedFile.writeLine("");

	return macroName;
}

kodgen::uint16 GeneratedClassCodeTemplate::computeMethodFlags(kodgen::MethodInfo const& method) const noexcept
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

kodgen::uint16 GeneratedClassCodeTemplate::computeFieldFlags(kodgen::FieldInfo const& field) const noexcept
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

std::string GeneratedClassCodeTemplate::getFullMethodPrototype(kodgen::StructClassInfo const& classInfo, kodgen::MethodInfo const& method) const noexcept
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

std::string GeneratedClassCodeTemplate::generateDefaultInstantiateMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_DefaultInstantiateDefinition";

	generatedFile.writeMacro(std::string(macroName),
								"private:",
								"	template <typename T>",
								"	static void* __RFKinstantiate() noexcept",
								"	{",
								"		if constexpr (std::is_default_constructible_v<T>)",
								"			return new T();",
								"		else",
								"			return nullptr;",
								"	}");

	return macroName;
}

std::string GeneratedClassCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_RegisterArchetype";

	//Use the default registerer constructor when there is an outer entity
	//It will not register the type to the database.
	//This field is still necessary because it is used to know is a struct/class is reflected or not.
	std::string fieldValue = (info.outerEntity == nullptr) ? " = &staticGetArchetype();" : ";";

	generatedFile.writeMacro(std::string(macroName),
							 "private:",
							 "	static inline rfk::ArchetypeRegisterer __rfkArchetypeRegisterer" +  fieldValue);

	generatedFile.writeLine("");

	return macroName;
}