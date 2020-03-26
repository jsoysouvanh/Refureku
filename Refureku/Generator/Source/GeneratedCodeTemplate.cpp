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
	std::string mainMacroName	 = _externalMacroPrefix + classInfo.name + "_GENERATED";

	std::string getTypeMacroName = generateGetTypeMacro(generatedFile, classInfo);

	generatedFile.writeMacro(	std::move(mainMacroName),
								 "friend refureku::Type;",
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

std::string GeneratedCodeTemplate::generateGetTypeMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string getTypeMacroName					= _internalMacroPrefix + info.name + "_GetTypeMacro";
	std::string generatedMethodsMetadataMacroName	= generateMethodsMetadataMacro(generatedFile, info);
	std::string generatedParentsMetadataMacroName	= generateParentsMetadataMacro(generatedFile, info);

	generatedFile.writeMacro(std::string(getTypeMacroName),
								"public:",
								"	static refureku::Type const& staticGetType() noexcept",
								"	{",
								"		static bool				initialized = false;",
								"		static refureku::Type	type(\"" + info.name + "\", "
																		+ std::to_string(_stringHasher(info.name)) + ", "
																		+ "static_cast<refureku::Type::ECategory>(" + std::to_string(static_cast<kodgen::uint8>(info.entityType)) + "));",
								"	",
								"		if (!initialized)",
								"		{",
								"			" + std::move(generatedParentsMetadataMacroName),
								"			" + std::move(generatedMethodsMetadataMacroName),
								"",
								"			initialized = true;",
								"		}",
								"	",
								"		return type;",
								"	}",
								"	",
								"	refureku::Type const& getType() const noexcept",
								"	{",
								"		return " + info.name + "::staticGetType();",
								"	}"
							 );

	return getTypeMacroName;
}

std::string GeneratedCodeTemplate::generateMethodsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	std::string macroName = _internalMacroPrefix + info.name + "_GenerateMethodsMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	//Keep track of what we add so that we save some checks in the metadata
	std::vector<kodgen::MethodInfo const*>	nonStaticMethods;
	std::vector<kodgen::MethodInfo const*>	staticMethods;

	//Add required methods (instantiate....)
	generatedFile.writeLine("	type.addRequiredMethods<" + info.name + ">(); \t\\");

	//Sort methods so that it doesn't have to be done in the target program
	sortMethods(info.methods, nonStaticMethods, staticMethods);

	//Fill the target type method vectors using sorted methods we just computed
	//Reserve only the memory we need
	generatedFile.writeLine("	type.staticMethods.reserve(" + std::to_string(staticMethods.size()) + ");\t\\");
	
	for (kodgen::MethodInfo const* method : staticMethods)
	{
		std::string functionType = "refureku::NonMemberFunction<" + std::move(method->getPrototype(true)) + ">";

		generatedFile.writeLine("	type.staticMethods.emplace_back(\"" + method->name + "\", " +
								std::to_string(_stringHasher(info.name + method->name + method->getPrototype(true, true))) +
								", static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(method->accessSpecifier)) + ")" +
								", std::shared_ptr<" + functionType + ">(new " + std::move(functionType) + "(& " + info.name + "::" + method->name + ")));\t\\");
	}

	//Reserve only the memory we need
	generatedFile.writeLine("	type.methods.reserve(" + std::to_string(nonStaticMethods.size()) + ");\t\\");

	for (kodgen::MethodInfo const* method : nonStaticMethods)
	{
		std::string memberFunctionType = "refureku::MemberFunction<" + info.name + ", " + std::move(method->getPrototype(true)) + ">";

		generatedFile.writeLine("	type.methods.emplace_back(\"" + method->name + "\", " +
								std::to_string(_stringHasher(info.name + method->name + method->getPrototype(true, true))) +
								", static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(method->accessSpecifier)) + ")" +
								", &type, std::shared_ptr<" + memberFunctionType + ">(new " + std::move(memberFunctionType) + "(& " + info.name + "::" + method->name + ")));\t\\");
	}
	
	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedCodeTemplate::generateParentsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	if (!info.parents.empty())
	{
		std::string macroName = _internalMacroPrefix + info.name + "_GenerateParentsMetadata";

		generatedFile.writeLine("#define " + macroName + "\t\\");

		generatedFile.writeLine("	type.directParents.reserve(" + std::to_string(info.parents.size()) + ");\t\\");

		for (kodgen::StructClassInfo::ParentInfo parent : info.parents)
		{
			generatedFile.writeLine("	type.addToParentsIfPossible<" + parent.type.getName(true) + ">(static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(parent.inheritanceAccess)) + "));\t\\");
		}

		generatedFile.writeLine("");

		return macroName;
	}
	
	//No parents, don't bother generate a macro
	return std::string();
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