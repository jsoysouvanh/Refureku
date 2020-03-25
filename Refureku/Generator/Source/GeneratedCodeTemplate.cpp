#include "GeneratedCodeTemplate.h"

#include <unordered_set>
#include <cassert>

#include "Misc/FundamentalTypes.h"

using namespace refureku;

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
	std::string mainMacroName	 = "RFRK" + classInfo.name + "_GENERATED";

	std::string getTypeMacroName = generateGetTypeMacro(generatedFile, classInfo);

	generatedFile.writeMacro(	std::move(mainMacroName),
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
	std::string getTypeMacroName					= "RFRK" + info.name + "_GetTypeMacro";
	std::string generatedMethodsMetadataMacroName	= generateMethodsMetadataMacro(generatedFile, info);
	std::string generatedParentsMetadataMacroName	= generateParentsMetadataMacro(generatedFile, info);

	generatedFile.writeMacro(std::string(getTypeMacroName),
								"public:",
								"	static refureku::Type const& staticGetType() noexcept",
								"	{",
								"		static bool				initialized = false;",
								"		static refureku::Type	type;",
								"	",
								"		if (!initialized)",
								"		{",
								"			type.name		= \"" + info.name + "\";",
								"			type.id			= " + std::to_string(std::hash<std::string>()(info.name)) + ";",
								"			type.category	= static_cast<refureku::Type::ECategory>(" + std::to_string(static_cast<kodgen::uint8>(info.entityType)) + ");",
								"",
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
	std::string macroName = "RFRK" + info.name + "_GenerateMethodsMetadata";

	generatedFile.writeLine("#define " + macroName + "\t\\");

	//Keep track of what we add so that we save some checks in the metadata
	std::unordered_set<std::string>				nonStaticMethods;
	std::unordered_set<std::string>				staticMethods;
	std::unordered_set<std::string>::iterator	it;

	for (auto& [accessSpecifier, methods] : info.methods)
	{
		for (kodgen::MethodInfo const& method : methods)
		{
			if (method.qualifiers.isStatic)
			{
				//Check if we have to emplace a new vector
				if ((it = staticMethods.find(method.name)) == staticMethods.end())
				{
					staticMethods.emplace(method.name);
					generatedFile.writeLine("	type.staticMethodsLookupTable.emplace(\"" + method.name + "\", std::vector<refureku::StaticMethod>());\t\\");
				}

				//Fill static method table lookup
				generatedFile.writeLine("	type.staticMethodsLookupTable[\"" + method.name + "\"].emplace_back(refureku::StaticMethod(new refureku::NonMemberFunction<" + method.prototype + ">(& " + info.name + "::" + method.name + ")));\t\\");
			}
			else
			{
				//Check if we have to emplace a new vector
				if ((it = nonStaticMethods.find(method.name)) == nonStaticMethods.end())
				{
					nonStaticMethods.emplace(method.name);
					generatedFile.writeLine("	type.methodsLookupTable.emplace(\"" + method.name + "\", std::vector<refureku::Method>());\t\\");
				}

				//Remove const from method prototype if any
				std::string methodProto(method.prototype);
				if (methodProto.back() == 't')	//If proto ends with a t, it should be the cons't'
					methodProto.resize(methodProto.size() - 5u);	//5 is the size of "const"

				//Fill method table lookup
				generatedFile.writeLine("	type.methodsLookupTable[\"" + method.name + "\"].emplace_back(refureku::Method(new refureku::MemberFunction<" + info.name + ", " + std::move(methodProto) + ">(& " + info.name + "::" + method.name + ")));\t\\");
			}
		}
	}

	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedCodeTemplate::generateParentsMetadataMacro(kodgen::GeneratedFile& generatedFile, kodgen::StructClassInfo const& info) const noexcept
{
	if (!info.parents.empty())
	{
		std::string macroName = "RFRK" + info.name + "_GenerateParentsMetadata";

		generatedFile.writeLine("#define " + macroName + "\t\\");

		generatedFile.writeLine("	type.parents.reserve(" + std::to_string(info.parents.at(kodgen::EAccessSpecifier::Private).size() +
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