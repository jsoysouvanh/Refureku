#include "RefurekuGenerator/CodeGen/GeneratedClassCodeTemplate.h"

#include <cassert>
#include <algorithm>

#include <Kodgen/Parsing/FileParserFactoryBase.h>	//For FileParser::parsingMacro
#include <Kodgen/InfoStructures/NestedStructClassInfo.h>
#include <Kodgen/InfoStructures/NestedEnumInfo.h>
#include <Kodgen/Misc/FundamentalTypes.h>

#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenClassFooterData.h"
#include "RefurekuGenerator/Misc/Helpers.h"

using namespace rfk;

void GeneratedClassCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& entityInfo, kodgen::FileGenerationUnit& fgu, std::string& out_errorDescription) const noexcept
{
	GeneratedEntityCodeTemplate::generateCode(generatedFile, entityInfo, fgu, out_errorDescription);

	switch (entityInfo.entityType)
	{
		case kodgen::EEntityType::Class:
			generateClassCode(generatedFile, static_cast<kodgen::StructClassInfo&>(entityInfo));
			break;

		case kodgen::EEntityType::Struct:
			generateStructCode(generatedFile, static_cast<kodgen::StructClassInfo&>(entityInfo));
			break;

		default:
			assert(false);	//Should never reach this point
	}
}

std::vector<std::string> GeneratedClassCodeTemplate::generateCustomCodeMacros(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	std::vector<std::string> result;

	result.emplace_back(generateGetArchetypeMacro(generatedFile, info));
	result.emplace_back(generateRegistrationMacro(generatedFile, info));

	std::string nativePropsMacro = generateNativePropsMacro(generatedFile, info);
	if (!nativePropsMacro.empty())
		result.emplace_back(std::move(nativePropsMacro));

	return result;
}

std::string GeneratedClassCodeTemplate::getMainMacroName(kodgen::StructClassInfo& info) const noexcept
{
	return externalPrefix + info.name + "_GENERATED";
}

void GeneratedClassCodeTemplate::generateClassCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& classInfo) const noexcept
{
	std::string mainMacroName								= getMainMacroName(classInfo);
	std::vector<std::string> generateCustomCodeMacroNames	= generateCustomCodeMacros(generatedFile, classInfo);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParserFactoryBase::parsingMacro);

	generatedFile.writeMacro(std::string(mainMacroName));

	generatedFile.writeLine("#else");

	//Define the main macro
	generatedFile.writeLines("#define " + std::move(mainMacroName) + "\t\\",
								"\tfriend rfk::Struct;	\t\\",
								"\tfriend rfk::hasField___rfkArchetypeRegisterer<" + classInfo.name + ", rfk::ArchetypeRegisterer>; \t\\");

	//Inject all custom macros in the main macro
	for (auto& macroName : generateCustomCodeMacroNames)
	{
		generatedFile.writeLine("\t" + std::move(macroName) + "\t\\");
	}

	generatedFile.writeLines("\tprivate:",
							 "#endif\n");
}

void GeneratedClassCodeTemplate::generateStructCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& structInfo) const noexcept
{
	generateClassCode(generatedFile, structInfo);
}

std::string GeneratedClassCodeTemplate::generateGetArchetypeMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	std::string					entityId								= getEntityId(info);
	std::string					getTypeMacroDeclaration					= internalPrefix + entityId + "_GetTypeDeclaration";
	std::string					getTypeMacroDefinition					= internalPrefix + entityId + "_GetTypeDefinition";
	std::string					generateParentsMetadataMacroName		= generateParentsMetadataMacro(generatedFile, info);
	std::array<std::string, 2>	generateFieldsMetadataMacroName			= generateFieldsMetadataMacros(generatedFile, info);
	std::string					generateMethodsMetadataMacroName		= generateMethodsMetadataMacro(generatedFile, info);
	std::string					generateArchetypePropertiesMacroName	= generateArchetypePropertiesMacro(generatedFile, info);
	std::string					generatedNestedClassesMetadataMacroName	= generateNestedArchetypesMetadataMacro(generatedFile, info);
	std::string					generatedInstantiatorMacroName			= generateRegisterDefaultInstantiator(generatedFile, info);

	std::string returnedType = (info.entityType == kodgen::EEntityType::Struct) ? "rfk::Struct" : "rfk::Class";
	
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
								"			" + std::move(generatedInstantiatorMacroName),
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

std::string GeneratedClassCodeTemplate::generateMethodsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateMethodsMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	if (!info.methods.empty())
	{
		generatedFile.writeLine("\t[[maybe_unused]] rfk::Method*		method			= nullptr;\t\\");
		generatedFile.writeLine("\t[[maybe_unused]] rfk::StaticMethod*	staticMethod	= nullptr;\t\\");
	}

	std::string generatedCode;
	std::string currentMethodVariable;
	for (kodgen::MethodInfo& method : info.methods)
	{
		if (method.isStatic)
		{
			generatedFile.writeLine("\tstaticMethod = type.addStaticMethod(\"" + method.name + "\", " +
									std::to_string(stringHasher(method.id)) + "u, "
									"rfk::Type::getType<" + method.returnType.getName() + ">(), "
									"std::make_unique<rfk::NonMemberFunction<" + method.getPrototype(true) + ">" + ">(static_cast<" + getFullMethodPrototype(info, method) + ">(& " + info.name + "::" + method.name + ")), "
									"static_cast<rfk::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) + "));\t\\");

			currentMethodVariable = "staticMethod";
		}
		else
		{
			generatedFile.writeLine("\tmethod = type.addMethod(\"" + method.name + "\", " +
									std::to_string(stringHasher(method.id)) + "u, "
									"rfk::Type::getType<" + method.returnType.getName() + ">(), "
									"std::make_unique<rfk::MemberFunction<" + info.name + ", " + method.getPrototype(true) + ">" + ">(static_cast<" + getFullMethodPrototype(info, method) + ">(& " + info.name + "::" + method.name + ")), "
									"static_cast<rfk::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) + "));\t\\");

			currentMethodVariable = "method";
		}

		//Setup parameters
		if (!method.parameters.empty())
		{
			//Add all parameters in a single string
			generatedCode = "\t" + currentMethodVariable + "->parameters.reserve(" + std::to_string(method.parameters.size()) + "); " + currentMethodVariable;

			for (kodgen::FunctionParamInfo const& param : method.parameters)
			{
				generatedCode += "->addParameter(\"" + param.name + "\", rfk::Type::getType<" + param.type.getName() + ">())";
			}

			//Write generated parameters string to file
			generatedFile.writeLine(generatedCode + ";\t\\");
		}

		//Add properties after the method has been fully setup
		//Parameters have been added at this point, so properties generated code can safely add additional checks
		if (method.isStatic)
		{
			//Add method properties
			method.properties.removeStartAndTrailSpaces();
			generatedCode = fillEntityProperties(method, "staticMethod->");
			if (!generatedCode.empty())
				generatedFile.writeLine("	" + generatedCode + "\t\\");
		}
		else
		{
			//Add method properties
			method.properties.removeStartAndTrailSpaces();
			generatedCode = fillEntityProperties(method, "method->");
			if (!generatedCode.empty())
				generatedFile.writeLine("\t" + generatedCode + "\t\\");

			//Base method properties must be inherited AFTER this method properties have been added
			if (method.isOverride)
			{
				generatedFile.writeLine("\tmethod->inheritBaseMethodProperties();\t\\");
			}
		}
	}

	generatedFile.writeLine("");

	return macroName;
}

std::array<std::string, 2> GeneratedClassCodeTemplate::generateFieldsMetadataMacros(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	std::array<std::string, 2> macroNames = { internalPrefix + getEntityId(info) + "_GenerateFieldsMetadata" };

	generatedFile.writeLine("#define " + macroNames[0] + "\t\\");

	generatedFile.writeLine("	registerChild<" + info.name + ">(&type);\t\\");
	generatedFile.writeLine("");

	//Wrap this part in a method so that children classes can use it too
	macroNames[1] = generateFieldHelperMethodsMacro(generatedFile, info);

	return macroNames;
}

std::string GeneratedClassCodeTemplate::generateFieldHelperMethodsMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateFieldHelperMethods";

	//Generate parent registering templated method to discard calls on non reflected parents
	generatedFile.writeLines("#define " + macroName + "\t\\",
							"private:\t\\",
							 "	template <typename ParentType, typename ChildType>\t\\",
							 "	static constexpr void recurseRegisterChild([[maybe_unused]] rfk::Struct* childArchetype)\t\\",
							 "	{\t\\",
							 "		if constexpr (rfk::isReflectedClass<ParentType>)\t\\",
							 "		{\t\\",
							 "			ParentType::template registerChild<ChildType>(childArchetype);\t\\",
							 "		}\t\\",
							 "	}\t\\",
							 "public:\t\\",
							 "	template <typename ChildType>\t\\",
							 "	static void registerChild(rfk::Struct* childArchetype) noexcept\t\\",
							 "	{\t\\");

	for (kodgen::StructClassInfo::ParentInfo const& parent : info.parents)
	{
		generatedFile.writeLine("		recurseRegisterChild<" + parent.type.getName(true) + ", ChildType>(childArchetype);\t\\");
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
		generatedFile.writeLine("		[[maybe_unused]] rfk::Field*		field		= nullptr; \t\\");
		generatedFile.writeLine("		[[maybe_unused]] rfk::StaticField*	staticField = nullptr; \t\\");

		generatedFile.writeLines("		__RFK_DISABLE_WARNING_PUSH\t\\",
								 "		__RFK_DISABLE_WARNING_OFFSETOF\t\\");

		std::string properties;
		std::string currentFieldVariable;
		for (kodgen::FieldInfo& field : info.fields)
		{
			if (field.isStatic)
			{
				generatedFile.writeLine("		staticField = childArchetype->addStaticField(\"" + field.name + "\", " +
										std::to_string(stringHasher(field.id)) + "u, "
										"rfk::Type::getType<" + field.type.getName() + ">(), "
										"static_cast<rfk::EFieldFlags>(" + std::to_string(computeFieldFlags(field)) + "), "
										"&thisArchetype, "
										"&" + info.name + "::" + field.name + ");\t\\");

				currentFieldVariable = "staticField->";
			}
			else
			{
				generatedFile.writeLine("		field = childArchetype->addField(\"" + field.name + "\", " +
										std::to_string(stringHasher(field.id)) + "u, "
										"rfk::Type::getType<" + field.type.getName() + ">(), "
										"static_cast<rfk::EFieldFlags>(" + std::to_string(computeFieldFlags(field)) + "), "
										"&thisArchetype, "
										"offsetof(ChildType, " + field.name + "));\t\\");

				currentFieldVariable = "field->";
			}

			//Add properties
			field.properties.removeStartAndTrailSpaces();
			properties = fillEntityProperties(field, currentFieldVariable);
			if (!properties.empty())
				generatedFile.writeLine("	" + properties + "\t\\");
		}

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
			generatedFile.writeLine("	type.addToParents<" + parent.type.getName(true) + ">(static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));\t\\");
		}

		generatedFile.writeLine("");

		return macroName;
	}
	
	//No parents, don't bother generate a macro
	return std::string();
}

std::string GeneratedClassCodeTemplate::generateNestedArchetypesMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	kodgen::uint64 nestedArchetypesCount = info.nestedStructs.size() + info.nestedClasses.size() + info.nestedEnums.size();

	if (nestedArchetypesCount == 0u)
	{
		//No nested archetypes, don't bother generate a macro
		return std::string();
	}

	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateNestedArchetypesMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	generatedFile.writeLine("	rfk::Archetype* archetype = nullptr;\t\\");

	//Reserve memory first
	generatedFile.writeLine("	type.nestedArchetypes.reserve(" + std::to_string(nestedArchetypesCount) + ");\t\\");
	
	//Add nested structs
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedStruct : info.nestedStructs)
	{
		generatedFile.writeLine("	archetype = type.addNestedArchetype(&" + nestedStruct->name + "::staticGetArchetype(), "
								"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedStruct->accessSpecifier)) + "));\t\\");
	}

	//Add nested classes
	for (std::shared_ptr<kodgen::NestedStructClassInfo> const& nestedClass : info.nestedClasses)
	{
		generatedFile.writeLine("	archetype = type.addNestedArchetype(&" + nestedClass->name + "::staticGetArchetype(), "
								"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedClass->accessSpecifier)) + "));\t\\");
	}

	//Add nested enums
	for (kodgen::NestedEnumInfo const& nestedEnum : info.nestedEnums)
	{
		generatedFile.writeLine("	archetype = type.addNestedArchetype(rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">(), "
								"static_cast<rfk::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(nestedEnum.accessSpecifier)) + "));\t\\");
	}

	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedClassCodeTemplate::generateRegisterDefaultInstantiator(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo& info) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(info) + "_GenerateDefaultInstantiatorSetup";

	generatedFile.writeMacro(std::string(macroName), "type.setDefaultInstantiator(&rfk::defaultInstantiator<" + info.name + ">);");

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

std::string GeneratedClassCodeTemplate::generateNativePropsMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string						macroName = internalPrefix + getEntityId(info) + "_NativeProperties";
	std::string						generatedCode;
	PropertyCodeGenClassFooterData	data;

	//Find all native properties in entities nested directly in this class
	//Self properties
	generatedCode += generateNativePropertiesCode(info, &data);
	
	//Fields
	for (kodgen::EntityInfo const& entityInfo : info.fields)
	{
		generatedCode += generateNativePropertiesCode(entityInfo, &data);
	}

	//Methods
	for (kodgen::EntityInfo const& entityInfo : info.methods)
	{
		generatedCode += generateNativePropertiesCode(entityInfo, &data);
	}

	//Nested enums
	for (kodgen::EntityInfo const& entityInfo : info.nestedEnums)
	{
		generatedCode += generateNativePropertiesCode(entityInfo, &data);
	}

	//Don't generate native properties code for nested structs and classes as it will be generated in their own footer

	if (generatedCode.empty())
	{
		//Don't generate the macro if there's no generated code
		return "";
	}
	else
	{
		generatedFile.writeMacro(std::string(macroName), std::move(generatedCode), "");

		return macroName;
	}
}