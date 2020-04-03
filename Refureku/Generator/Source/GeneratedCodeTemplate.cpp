#include "GeneratedCodeTemplate.h"

#include <unordered_set>
#include <cassert>
#include <algorithm>

#include "Misc/FundamentalTypes.h"
#include "Keywords.h"

using namespace rfk;

std::hash<std::string> GeneratedCodeTemplate::_stringHasher;

void GeneratedCodeTemplate::undefMacros(kodgen::GeneratedFile& generatedFile, std::string const& generatedMacroName) const noexcept
{
	//TODO
}

void GeneratedCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) const noexcept
{
	switch (entityInfo.entityType)
	{
		case kodgen::EntityInfo::EType::Class:
			generateClassCode(generatedFile, static_cast<kodgen::StructClassInfo const&>(entityInfo));
			break;

		case kodgen::EntityInfo::EType::Struct:
			generateStructCode(generatedFile, static_cast<kodgen::StructClassInfo const&>(entityInfo));
			break;

		case kodgen::EntityInfo::EType::Enum:
			generateEnumCode(generatedFile, static_cast<kodgen::EnumInfo const&>(entityInfo));
			break;

		default:
			assert(false);	//Should never reach this point
	}
}

void GeneratedCodeTemplate::generateClassCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& classInfo) const noexcept
{
	std::string mainMacroName					= _externalPrefix + classInfo.name + "_GENERATED";

	std::string getTypeMacroName				= generateGetArchetypeMacro(generatedFile, classInfo);
	std::string defaultInstantiateMacro			= generateDefaultInstantiateMacro(generatedFile, classInfo);
	std::string generateRegistrationMacroName	= generateRegistrationMacro(generatedFile, classInfo);

	generatedFile.writeMacro(std::move(mainMacroName),
								"friend rfk::Archetype;",
								"friend rfk::Struct;",
								"friend rfk::Class;",
									std::move(defaultInstantiateMacro),
									std::move(getTypeMacroName),
									std::move(generateRegistrationMacroName),
								"private:");
}

void GeneratedCodeTemplate::generateStructCode(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& structInfo) const noexcept
{
	//std::string mainMacroName	 = "RFRK" + structInfo.name + "_GENERATED";

	//std::string getTypeMacroName = generateGetTypeMacro(generatedFile, structInfo);

	//generatedFile.writeMacro(std::move(mainMacroName),
	//						 std::move(getTypeMacroName),
	//						 "public:");
}

void GeneratedCodeTemplate::generateEnumCode(kodgen::GeneratedFile& generatedFile, kodgen::EnumInfo const& enumInfo) const noexcept
{

}

std::string GeneratedCodeTemplate::generateGetArchetypeMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string					getTypeMacroName						= _internalPrefix + info.name + "_GetTypeMacro";
	std::string					generateParentsMetadataMacroName		= generateParentsMetadataMacro(generatedFile, info);
	std::array<std::string, 2>	generateFieldsMetadataMacroName			= generateFieldsMetadataMacros(generatedFile, info);
	std::string					generateMethodsMetadataMacroName		= generateMethodsMetadataMacro(generatedFile, info);
	std::string					generateArchetypePropertiesMacroName	= generateArchetypePropertiesMacro(generatedFile, info);

	std::string returnedType = (info.entityType == kodgen::EntityInfo::EType::Struct) ? "rfk::Struct" : "rfk::Class";
	
	bool shouldGenerateGetArchetype = std::find_if(info.properties.simpleProperties.cbegin(),
												   info.properties.simpleProperties.cend(),
												   [](kodgen::SimpleProperty const& p) { return p.name == __RFK_CLASS_REFLECTED; }) != info.properties.simpleProperties.cend();

	std::string getArchetypeMethod = (shouldGenerateGetArchetype) ?
		returnedType + " const& getArchetype() const noexcept override { return " + info.name + "::staticGetArchetype(); }" : "";

	generatedFile.writeMacro(std::string(getTypeMacroName),
								std::move(generateFieldsMetadataMacroName[1]),
								"public:",
								"	static " + returnedType + " const& staticGetArchetype() noexcept",
								"	{",
								"		static bool				initialized = false;",
								"		static " + returnedType + " type(\"" + info.name + "\", "
																		+ std::to_string(_stringHasher(info.id)) + "u, "
																		+ "static_cast<rfk::Archetype::ECategory>(" + std::to_string(static_cast<kodgen::uint8>(info.entityType)) + "), "
																		+ "sizeof(" + info.name + "));",
								"	",
								"		if (!initialized)",
								"		{",
								"			initialized = true;",
								"	",
								"			" + std::move(generateArchetypePropertiesMacroName),
								"			" + std::move(generateParentsMetadataMacroName),
								"			" + std::move(generateFieldsMetadataMacroName[0]),
								"			" + std::move(generateMethodsMetadataMacroName),
								"		}",
								"	",
								"		return type;",
								"	}",
								"	",
								"	" + getArchetypeMethod
							 );

	return getTypeMacroName;
}

std::string GeneratedCodeTemplate::generateArchetypePropertiesMacro(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_GenerateArchetypeProperties";

	generatedFile.writeMacro(std::string(macroName), fillEntityProperties(info, "type."));

	return macroName;
}

std::string GeneratedCodeTemplate::generateMethodsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_GenerateMethodsMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	if (!info.methods.empty())
	{
		generatedFile.writeLine("	std::unordered_multiset<rfk::Method, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator			methodsIt;\t\\");
		generatedFile.writeLine("	std::unordered_multiset<rfk::StaticMethod, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator	staticMethodsIt;\t\\");
		generatedFile.writeLine("	rfk::MethodBase*																						currMethod = nullptr;\t\\");
	}

	std::string functionType;
	std::string methodName;
	std::string properties;
	for (kodgen::MethodInfo const& method : info.methods)
	{
		if (method.qualifiers.isStatic)
		{
			functionType = "rfk::NonMemberFunction<" + method.getPrototype(true) + ">";
			methodName = method.getName();

			generatedFile.writeLine("	staticMethodsIt = type.staticMethods.emplace(\"" + methodName + "\", " +
									std::to_string(_stringHasher(method.id)) +
									"u, static_cast<rfk::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) +
									"), std::shared_ptr<" + functionType + ">(new " + functionType + "(& " + info.name + "::" + methodName + ")));\t\\");

			generatedFile.writeLine("	currMethod = const_cast<rfk::StaticMethod*>(&*staticMethodsIt);\t\\");
		}
		else
		{
			functionType = "rfk::MemberFunction<" + info.name + ", " + method.getPrototype(true) + ">";
			methodName = method.getName();

			generatedFile.writeLine("	methodsIt = type.methods.emplace(\"" + methodName + "\", " +
									std::to_string(_stringHasher(method.id)) +
									"u, static_cast<rfk::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) +
									"), std::shared_ptr<" + functionType + ">(new " + functionType + "(& " + info.name + "::" + methodName + ")), &type);\t\\");

			generatedFile.writeLine("	currMethod = const_cast<rfk::Method*>(&*methodsIt);\t\\");
		}

		//Add properties
		properties = fillEntityProperties(method, "currMethod->");
		if (!properties.empty())
			generatedFile.writeLine("	" + properties + "\t\\");

		//Setup return type
		generatedFile.writeLine("	currMethod->returnType = rfk::Database::getType<" + method.returnType.getName() + ">();\t\\");

		//Setup parameters
		if (!method.parameters.empty())
		{
			generatedFile.writeLine("	currMethod->parameters.reserve(" + std::to_string(method.parameters.size()) + ");\t\\");

			for (kodgen::MethodParamInfo const& param : method.parameters)
			{
				generatedFile.writeLine("	currMethod->parameters.emplace_back(\"" + param.name + "\", rfk::Type(rfk::Database::getType<" + param.type.getName() + ">()));\t\\");
			}
		}
	}

	//Add required methods (instantiate....)
	generatedFile.writeLine("	type.__RFKaddRequiredMethods<" + info.name + ">();\t\\");

	generatedFile.writeLine("");

	return macroName;
}

std::array<std::string, 2> GeneratedCodeTemplate::generateFieldsMetadataMacros(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::array<std::string, 2> macroNames = { _internalPrefix + info.name + "_GenerateFieldsMetadata" };

	generatedFile.writeLine("#define " + macroNames[0] + "\t\\");

	generatedFile.writeLine("	__RFKregisterChild<" + info.name + ">(&type);\t\\");
	generatedFile.writeLine("");

	//Wrap this part in a method so that children classes can use it too
	macroNames[1] = generateFieldHelperMethodsMacro(generatedFile, info);

	return macroNames;
}

std::string GeneratedCodeTemplate::generateFieldHelperMethodsMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_GenerateFieldHelperMethods";

	//Generate parent registering templated method to discard calls on non reflected parents
	generatedFile.writeLines("#define " + macroName + "\t\\",
							"private:\t\\",
							 "	template <typename ParentType, typename ChildType>\t\\",
							 "	static constexpr void __RFKrecurseRegisterChild(rfk::Struct* childArchetype)\t\\",
							 "	{\t\\",
							 "		if constexpr (rfk::generated::implements_staticGetArchetype<ParentType, rfk::Class const&()>::value)\t\\",
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

	if (!info.fields.empty())
	{
		generatedFile.writeLine("		std::unordered_multiset<rfk::Field, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator			fieldsIt;\t\\");
		generatedFile.writeLine("		std::unordered_multiset<rfk::StaticField, rfk::Entity::NameHasher, rfk::Entity::EqualName>::iterator	staticFieldsIt;\t\\");
		generatedFile.writeLine("		rfk::FieldBase*																							currField = nullptr;\t\\");
	}

	std::string properties;
	for (kodgen::FieldInfo const& field : info.fields)
	{
		if (field.qualifiers.isStatic)
		{
			generatedFile.writeLine("		staticFieldsIt = childArchetype->staticFields.emplace(\"" + field.name + "\", " +
									std::to_string(_stringHasher(field.id)) +
									"u, static_cast<rfk::EFieldFlags>(" + std::to_string(computeFieldFlags(field)) +
									"), childArchetype, &thisArchetype, &" + info.name + "::" + field.name + ");\t\\");

			generatedFile.writeLine("		currField = const_cast<rfk::StaticField*>(&*staticFieldsIt);\t\\");
		}
		else
		{
			generatedFile.writeLine("		fieldsIt = childArchetype->fields.emplace(\"" + field.name + "\", " +
									std::to_string(_stringHasher(field.id)) +
									"u, static_cast<rfk::EFieldFlags>(" + std::to_string(computeFieldFlags(field)) +
									"), childArchetype, &thisArchetype, offsetof(ChildType, " + field.name + ")" + ", " + std::to_string(field.qualifiers.isMutable) + ");\t\\");

			generatedFile.writeLine("		currField = const_cast<rfk::Field*>(&*fieldsIt);\t\\");
		}

		//Make type
		generatedFile.writeLine("		currField->type = rfk::Database::getType<" + field.type.getName() + ">();\t\\");

		//Add properties
		properties = fillEntityProperties(field, "	currField->");
		if (!properties.empty())
			generatedFile.writeLine("	" + properties + "\t\\");
	}

	generatedFile.writeLine("	}");

	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedCodeTemplate::generateParentsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	if (!info.parents.empty())
	{
		std::string macroName = _internalPrefix + info.name + "_GenerateParentsMetadata";

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

kodgen::uint16 GeneratedCodeTemplate::computeMethodFlags(kodgen::MethodInfo const& method) const noexcept
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

	if (method.qualifiers.isStatic)
		result |= 1 << 3;

	if (method.qualifiers.isInline)
		result |= 1 << 4;

	if (method.qualifiers.isVirtual)
		result |= 1 << 5;

	if (method.qualifiers.isPureVirtual)
		result |= 1 << 6;

	if (method.qualifiers.isOverride)
		result |= 1 << 7;

	if (method.qualifiers.isFinal)
		result |= 1 << 8;

	if (method.qualifiers.isConst)
		result |= 1 << 9;

	return result;
}
kodgen::uint16 GeneratedCodeTemplate::computeFieldFlags(kodgen::FieldInfo const& field) const noexcept
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

	if (field.qualifiers.isStatic)
		result |= 1 << 3;

	if (field.qualifiers.isMutable)
		result |= 1 << 4;

	return result;
}

std::string GeneratedCodeTemplate::generateDefaultInstantiateMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_DefaultInstantiateMacro";

	generatedFile.writeMacro(std::string(macroName),
								"private:",
								"	template <typename T>",
								"	static void* __RFKinstantiate() noexcept",
								"	{",
								"		if constexpr (std::is_default_constructible_v<T>)",
								"			return new " + info.name + "();",
								"		else",
								"			return nullptr;",
								"	}");

	return macroName;
}

std::string GeneratedCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_RegisterArchetype";

	generatedFile.writeMacro(std::string(macroName),
							 "static inline rfk::ArchetypeRegisterer reg = staticGetArchetype();");

	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedCodeTemplate::fillEntityProperties(kodgen::EntityInfo const& info, std::string const& entityVarName) const noexcept
{
	std::string result;

	for (kodgen::SimpleProperty const& prop : info.properties.simpleProperties)
	{
		result += entityVarName + "properties.simpleProperties.emplace(\"" + prop.name + "\"); ";
	}

	for (kodgen::ComplexProperty const& prop : info.properties.complexProperties)
	{
		for (std::string subProp : prop.subProperties)
		{
			result += entityVarName + "properties.complexProperties.emplace(\"" + prop.name + "\", \"" + subProp + "\"); ";
		}
	}

	return result;
}