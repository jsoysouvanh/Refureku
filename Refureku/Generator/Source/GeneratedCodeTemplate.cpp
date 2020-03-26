#include "GeneratedCodeTemplate.h"

#include <unordered_set>
#include <cassert>

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
	std::unordered_set<std::string>				nonStaticMethods;
	std::unordered_set<std::string>				staticMethods;
	std::unordered_set<std::string>::iterator	it;

	generatedFile.writeLine("	type.addRequiredMethods<" + info.name + ">(); \t\\");



	for (auto& [accessSpecifier, methods] : info.methods)
	{
		for (kodgen::MethodInfo const& method : methods)
		{
			//Remove qualifiers from method prototype if any (const, noexcept...)
			std::string methodProto = method.getPrototype(true);

			if (method.qualifiers.isStatic)
			{
				generatedFile.writeLine("	type.staticMethods.emplace_back(refureku::StaticMethod(\"" + method.name + "\", " +
										std::to_string(_stringHasher(info.name + method.name + method.getPrototype(true, true))) +
										", static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(accessSpecifier)) + ")" +
										", new refureku::NonMemberFunction<" + std::move(methodProto) + ">(& " + info.name + "::" + method.name + ")));\t\\");
			}
			else
			{
				generatedFile.writeLine("	type.methods.emplace_back(refureku::Method(\"" + method.name + "\", " +
										std::to_string(_stringHasher(info.name + method.name + method.getPrototype(true, true))) +
										", static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(accessSpecifier)) + ")" +
										", &type, new refureku::MemberFunction<" + info.name + ", " + std::move(methodProto) + ">(& " + info.name + "::" + method.name + ")));\t\\");
			}
		}
		
		//TODO: resize + sort by name + proto
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

		generatedFile.writeLine("	type.directParents.reserve(" + std::to_string(info.parents.at(kodgen::EAccessSpecifier::Private).size() +
								info.parents.at(kodgen::EAccessSpecifier::Protected).size() +
								info.parents.at(kodgen::EAccessSpecifier::Public).size()) + ");	\t\\");

		for (auto& [access, parents] : info.parents)
		{
			for (auto& parent : parents)
			{
				generatedFile.writeLine("	type.addToParentsIfPossible<" + parent.getName(true) + ">(static_cast<refureku::EAccessSpecifier>(" + std::to_string(static_cast<kodgen::uint8>(access)) + "));\t\\");
			}
		}

		generatedFile.writeLine("");

		return macroName;
	}
	
	//No parents, don't bother generate a macro
	return std::string();
}