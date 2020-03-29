#include "GeneratedCodeTemplate.h"

#include <unordered_set>
#include <cassert>
#include <algorithm>

#include "Misc/FundamentalTypes.h"

using namespace refureku;

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
	std::string mainMacroName			= _externalPrefix + classInfo.name + "_GENERATED";

	std::string getTypeMacroName		= generateGetArchetypeMacro(generatedFile, classInfo);
	std::string defaultInstantiateMacro	= generateDefaultInstantiateMacro(generatedFile, classInfo);

	generatedFile.writeMacro(std::move(mainMacroName),
								"friend refureku::Archetype;",
								"friend refureku::Struct;",
								"friend refureku::Class;",
								"private:",
									std::move(defaultInstantiateMacro),
								"protected:",
								"public:",
									std::move(getTypeMacroName),
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
	std::string					getTypeMacroName					= _internalPrefix + info.name + "_GetTypeMacro";
	std::string					generatedParentsMetadataMacroName	= generateParentsMetadataMacro(generatedFile, info);
	std::array<std::string, 2>	generateFieldsMetadataMacroName		= generateFieldsMetadataMacros(generatedFile, info);
	std::string					generatedMethodsMetadataMacroName	= generateMethodsMetadataMacro(generatedFile, info);

	std::string returnedType = (info.entityType == kodgen::EntityInfo::EType::Struct) ? "refureku::Struct" : "refureku::Class";
	
	generatedFile.writeMacro(std::string(getTypeMacroName),
								"	static " + returnedType + " const& staticGetArchetype() noexcept",
								"	{",
								"		static bool				initialized = false;",
								"		static " + returnedType + " type(\"" + info.name + "\", "
																		+ std::to_string(_stringHasher(info.id)) + "u, "
																		+ "static_cast<refureku::Archetype::ECategory>(" + std::to_string(static_cast<kodgen::uint8>(info.entityType)) + "), "
																		+ "sizeof(" + info.name + "));",
								"	",
								"		if (!initialized)",
								"		{",
								"			" + std::move(generatedParentsMetadataMacroName),
								"			" + std::move(generateFieldsMetadataMacroName[0]) + "();",
								"			" + std::move(generatedMethodsMetadataMacroName),
								"",
								"			initialized = true;",
								"		}",
								"	",
								"		return type;",
								"	}",
								"	",
								"	" + returnedType + " const& getArchetype() const noexcept",
								"	{",
								"		return " + info.name + "::staticGetArchetype();",
								"	}"
							 );

	return getTypeMacroName;
}

std::string GeneratedCodeTemplate::generateMethodsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_GenerateMethodsMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	//Keep track of what we add so that we save some checks in the metadata
	std::vector<kodgen::MethodInfo const*>	nonStaticMethods;
	std::vector<kodgen::MethodInfo const*>	staticMethods;

	//Sort methods so that it doesn't have to be done in the target program
	sortMethods(info.methods, nonStaticMethods, staticMethods);

	//Fill the target type method vectors using sorted methods we just computed
	//Reserve only the memory we need
	generatedFile.writeLine("	type.staticMethods.reserve(" + std::to_string(staticMethods.size()) + ");\t\\");
	
	std::string functionType;
	std::string methodName;

	for (kodgen::MethodInfo const* method : staticMethods)
	{
		functionType = "refureku::NonMemberFunction<" + std::move(method->getPrototype(true)) + ">";
		methodName = method->getName();

		generatedFile.writeLine("	type.staticMethods.emplace_back(\"" + methodName + "\", " +
								std::to_string(_stringHasher(method->id)) +
								"u, static_cast<refureku::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) +
								"), std::shared_ptr<" + functionType + ">(new " + functionType + "(& " + info.name + "::" + methodName + ")));\t\\");
	}

	//Reserve only the memory we need
	generatedFile.writeLine("	type.methods.reserve(" + std::to_string(nonStaticMethods.size()) + ");\t\\");

	for (kodgen::MethodInfo const* method : nonStaticMethods)
	{
		functionType = "refureku::MemberFunction<" + info.name + ", " + std::move(method->getPrototype(true)) + ">";
		methodName = method->getName();

		generatedFile.writeLine("	type.methods.emplace_back(\"" + methodName + "\", " +
								std::to_string(_stringHasher(method->id)) +
								"u, static_cast<refureku::EMethodFlags>(" + std::to_string(computeMethodFlags(method)) +
								"), std::shared_ptr<" + functionType + ">(new " + functionType + "(& " + info.name + "::" + methodName + ")), &type);\t\\");
	}
	
	//Add required methods (instantiate....)
	generatedFile.writeLine("	type.__RFKaddRequiredMethods<" + info.name + ">(\"" + info.name + "*()\"); \t\\");

	generatedFile.writeLine("");

	return macroName;
}

std::array<std::string, 2> GeneratedCodeTemplate::generateFieldsMetadataMacros(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::array<std::string, 2> macroNames = {	_internalPrefix + info.name + "_GenerateFieldsMetadata",
												_internalPrefix + info.name + "_GenerateRegisterAndAppendMembersMethod" };

	generatedFile.writeLine("#define " + macroNames[0] + "\t\\");

	//Keep track of what we add so that we save some checks in the metadata
	std::vector<kodgen::FieldInfo const*>	nonStaticFields;
	std::vector<kodgen::FieldInfo const*>	staticFields;

	//Sort fields so that it doesn't have to be done in the target program
	sortFields(info.fields, nonStaticFields, staticFields);

	//Fill the target type method vectors using sorted methods we just computed
	//Reserve only the memory we need
	generatedFile.writeLine("	type.staticFields.reserve(" + std::to_string(staticFields.size()) + ");\t\\");

	for (kodgen::FieldInfo const* field : staticFields)
	{
		generatedFile.writeLine("	type.staticFields.emplace_back(\"" + field->name + "\", " +
								std::to_string(_stringHasher(field->id)) +
								"u, static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(field->accessSpecifier)) +
								"), &type, &type, &" + info.name + "::" + field->name + ");\t\\");
	}

	//Compute total number of fields for this type
	generatedFile.writeLine("	size_t fieldsCount = 0; std::vector<refureku::Struct::Parent> currParents; std::vector<refureku::Struct::Parent> nextParents = type.directParents; while (!nextParents.empty()) { std::swap(currParents, nextParents); nextParents.clear(); for (refureku::Struct::Parent const& parent : currParents) { nextParents.insert(nextParents.end(), parent.type->directParents.begin(), parent.type->directParents.end()); fieldsCount += parent.type->fields.size(); } }");

	//Reserve only the memory we need
	generatedFile.writeLine("	type.fields.reserve(fieldsCount);\t\\");
	
	//==============================================================
	/**
	*	TODO: REWORK HERE
	*/
	//Append own members to the fields collection - registerAndAppendMembers method is defined just below
	generatedFile.writeLine("	registerAndAppendMembers<" + info.name + ">(type, type.fields);\t\\");

	//==============================================================

	//Wrap this part in a method so that children classes can use it too
	//generatedFile.writeLines("#define " + macroNames[1] + "\t\\",
	//						 "template <typename T>	\t\\",
	//						 "static void " + info.name + "::registerAndAppendMembers(refureku::Struct const& archetype, std::vector<refureku::Field>& fields) noexcept {\t\\");

	generatedFile.writeLines("#define " + macroNames[1] + "\t\\",
							 "template <typename ChildType>\t\\",
							 "static void __RFKregisterChild(refureku::Struct* childArchetype) noexcept\t\\",
							 "{\t\\",
							 "refureku::Struct const& thisArchetype = staticGetArchetype();\t\\",
							 "//TODO: Recursive call to parents classes later here\t\\",
							 "//Add to list of children\t\\",
							 "if (childArchetype != &thisArchetype)\t\\",
							 "{\t\\",
							 "//TODO\t\\",
							 "}\t\\");

	for (kodgen::FieldInfo const* field : nonStaticFields)
	{
		generatedFile.writeLine("	childArchetype->fields.emplace_back(\"" + field->name + "\", " +
								std::to_string(_stringHasher(field->id)) +
								"u, static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(field->accessSpecifier)) +
								"), childArchetype, &thisArchetype, offsetof(ChildType, " + field->name + ")" + ", " + std::to_string(field->qualifiers.isMutable) + ");\t\\");
	}

		//Add fields
		//childArchetype->fields.emplace_back("somePtrToInt", 12635385505303968848u, static_cast<refureku::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, somePtrToInt), 0);

	generatedFile.writeLine("");

	return macroNames;
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
			generatedFile.writeLine("	type.__RFKaddToParents<" + parent.type.getName(true) + ">(static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));\t\\");
		}

		generatedFile.writeLine("");

		return macroName;
	}
	
	//No parents, don't bother generate a macro
	return std::string();
}

void GeneratedCodeTemplate::sortFields(std::vector<kodgen::FieldInfo> const& allFields, std::vector<kodgen::FieldInfo const*>& out_fields, std::vector<kodgen::FieldInfo const*>& out_staticFields) const noexcept
{
	out_fields.clear();
	out_staticFields.clear();

	//Insert all elements first, then sort them
	for (kodgen::FieldInfo const& field : allFields)
	{
		if (field.qualifiers.isStatic)
		{
			out_staticFields.emplace_back(&field);
		}
		else
		{
			out_fields.emplace_back(&field);
		}
	}

	std::sort(out_fields.begin(), out_fields.end(), [](kodgen::FieldInfo const* f1, kodgen::FieldInfo const* f2) { return f1->name < f2->name; });
	std::sort(out_staticFields.begin(), out_staticFields.end(), [](kodgen::FieldInfo const* f1, kodgen::FieldInfo const* f2) { return f1->name < f2->name; });
}

void GeneratedCodeTemplate::sortMethods(std::vector<kodgen::MethodInfo> const& allMethods, std::vector<kodgen::MethodInfo const*>& out_methods, std::vector<kodgen::MethodInfo const*>& out_staticMethods) const noexcept
{
	out_methods.clear();
	out_staticMethods.clear();

	for (kodgen::MethodInfo const& method : allMethods)
	{
		if (method.qualifiers.isStatic)
		{
			out_staticMethods.emplace_back(&method);
		}
		else
		{
			out_methods.emplace_back(&method);
		}
	}

	std::sort(out_methods.begin(), out_methods.end(), [](kodgen::MethodInfo const* m1, kodgen::MethodInfo const* m2) { return m1->name < m2->name; });
	std::sort(out_staticMethods.begin(), out_staticMethods.end(), [](kodgen::MethodInfo const* m1, kodgen::MethodInfo const* m2) { return m1->name < m2->name; });
}

kodgen::uint16 GeneratedCodeTemplate::computeMethodFlags(kodgen::MethodInfo const* method) const noexcept
{
	kodgen::uint16 result = 0;

	switch (method->accessSpecifier)
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

	if (method->qualifiers.isStatic)
		result |= 1 << 3;

	if (method->qualifiers.isInline)
		result |= 1 << 4;

	if (method->qualifiers.isVirtual)
		result |= 1 << 5;

	if (method->qualifiers.isPureVirtual)
		result |= 1 << 6;

	if (method->qualifiers.isOverride)
		result |= 1 << 7;

	if (method->qualifiers.isFinal)
		result |= 1 << 8;

	if (method->qualifiers.isConst)
		result |= 1 << 9;

	return result;
}
kodgen::uint16 GeneratedCodeTemplate::computeFieldFlags(kodgen::FieldInfo const* field) const noexcept
{
	return 0;
}

std::string GeneratedCodeTemplate::generateDefaultInstantiateMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalPrefix + info.name + "_DefaultInstantiateMacro";

	generatedFile.writeMacro(std::string(macroName),
								"template <typename T>",
								"static T* __RFKinstantiate() noexcept",
								"{",
								"	if constexpr (std::is_default_constructible<T>::value)",
								"		return new T();",
								"	else",
								"		return nullptr;",
								"}");

	return macroName;
}