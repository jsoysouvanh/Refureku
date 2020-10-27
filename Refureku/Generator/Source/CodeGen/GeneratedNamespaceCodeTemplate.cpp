#include "RefurekuGenerator/CodeGen/GeneratedNamespaceCodeTemplate.h"

#include <cassert>

#include <Kodgen/Parsing/FileParserFactoryBase.h>	//For FileParser::parsingMacro

#include "RefurekuGenerator/CodeGen/GeneratedVariableCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedFunctionCodeTemplate.h"
#include "RefurekuGenerator/Misc/Helpers.h"

using namespace rfk;

void GeneratedNamespaceCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo, kodgen::FileGenerationUnit& /* fgu */, std::string& /* out_errorDescription */) const noexcept
{
	assert(entityInfo.entityType == kodgen::EEntityType::Namespace);

	kodgen::NamespaceInfo const& namespaceInfo = static_cast<kodgen::NamespaceInfo const&>(entityInfo);

	std::string	mainMacroName						= internalPrefix + getEntityId(entityInfo) + "_GENERATED";

	std::string fillNamespaceDeclarationMacroName	= generateGetNamespaceFragmentDeclarationMacro(generatedFile, namespaceInfo);
	std::string fillNamespaceDefinitionMacroName	= generateGetNamespaceFragmentDefinitionMacro(generatedFile, namespaceInfo);
	std::string registerMacroName					= generateRegistrationMacro(generatedFile, namespaceInfo);

	//Hide namespace macro redefinition warning as it is likely to happen often
	ifDefUndefMacro(generatedFile, mainMacroName);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParserFactoryBase::parsingMacro);

	generatedFile.writeMacro(std::string(mainMacroName));

	generatedFile.writeLine("#else");

	generatedFile.writeMacro(std::move(mainMacroName),
							 "namespace rfk::generated {",
							 std::move(fillNamespaceDeclarationMacroName),
							 std::move(registerMacroName),
							 std::move(fillNamespaceDefinitionMacroName),
							 "}");

	generatedFile.writeLine("#endif\n");
}

std::string GeneratedNamespaceCodeTemplate::generateGetNamespaceFragmentDeclarationMacro(kodgen::GeneratedFile& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	std::string macroName = internalPrefix + getEntityId(namespaceInfo) + "_DeclareGetNamespaceFragment";

	ifDefUndefMacro(generatedFile, macroName);

	generatedFile.writeLines("#define " + macroName + " inline rfk::NamespaceFragment const& " + getGetNamespaceFragmentFunctionName(generatedFile, namespaceInfo) + "() noexcept;",
							 "");

	return macroName;
}

std::string GeneratedNamespaceCodeTemplate::generateGetNamespaceFragmentDefinitionMacro(kodgen::GeneratedFile& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	std::string entityId	= getEntityId(namespaceInfo);
	std::string macroName	= internalPrefix + entityId + "_DefineGetNamespaceFragment";

	ifDefUndefMacro(generatedFile, macroName);

	generatedFile.writeLines("#define " + macroName + "\t\\",
							 "	inline rfk::NamespaceFragment const& " + getGetNamespaceFragmentFunctionName(generatedFile, namespaceInfo) + "() noexcept\t\\",
							 "	{\t\\",
							 "		static rfk::NamespaceFragment	fragment(\"" + namespaceInfo.name + "\", " + entityId + ");\t\\",
							 "		static bool						initialized = false;\t\\",
							 "		if (!initialized)\t\\",
							 "		{\t\\",
							 "			initialized = true;\t\\"
							);

	//Fill namespace properties
	std::string properties = fillEntityProperties(namespaceInfo, "fragment.");
	if (!properties.empty())
	{
		generatedFile.writeLine("			" + properties + "\t\\");
	}

	kodgen::uint64 totalSize = namespaceInfo.namespaces.size() +
								namespaceInfo.structs.size() +
								namespaceInfo.classes.size() +
								namespaceInfo.enums.size() +
								namespaceInfo.variables.size() +
								namespaceInfo.functions.size();

	//Fill nested namespaces
	if (totalSize != 0u)
	{
		//Reserve space first
		generatedFile.writeLine("			fragment.nestedEntities.reserve(" + std::to_string(totalSize) + "u);\t\\");

		//Fill nested namespaces
		for (kodgen::NamespaceInfo const& nestedNamespace : namespaceInfo.namespaces)
		{
			generatedFile.writeLine("			fragment.nestedEntities.emplace_back(" + getNamespaceFragmentRegistererName(generatedFile, nestedNamespace) + ".getNamespaceInstance());\t\\");
		}

		//Fill nested structs
		for (kodgen::StructClassInfo const& nestedStruct : namespaceInfo.structs)
		{
			generatedFile.writeLine("			fragment.nestedEntities.emplace_back(&" + nestedStruct.type.getCanonicalName() + "::staticGetArchetype());\t\\");
		}

		//Fill nested classes
		for (kodgen::StructClassInfo const& nestedClass : namespaceInfo.classes)
		{
			generatedFile.writeLine("			fragment.nestedEntities.emplace_back(&" + nestedClass.type.getCanonicalName() + "::staticGetArchetype());\t\\");
		}

		//Fill nested enums
		for (kodgen::EnumInfo const& nestedEnum : namespaceInfo.enums)
		{
			generatedFile.writeLine("			fragment.nestedEntities.emplace_back(rfk::getEnum<" + nestedEnum.type.getCanonicalName() + ">());\t\\");
		}

		//Fill nested variables
		for (kodgen::VariableInfo const& variable : namespaceInfo.variables)
		{
			generatedFile.writeLine("			fragment.nestedEntities.emplace_back(&" + GeneratedVariableCodeTemplate::getGetVariableFunctionName(variable) + "());\t\\");
		}

		//Fill nested functions
		for (kodgen::FunctionInfo const& function : namespaceInfo.functions)
		{
			generatedFile.writeLine("			fragment.nestedEntities.emplace_back(&" + GeneratedFunctionCodeTemplate::getGetFunctionFunctionName(function) + "());\t\\");
		}
	}

	generatedFile.writeLines("		}\t\\",
							 "	return fragment;\t\\",
							 "	}",
							 "");

	return macroName;
}

std::string GeneratedNamespaceCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	std::string entityId	= getEntityId(namespaceInfo);
	std::string macroName	= internalPrefix + entityId + "_RegisterNamespace";

	ifDefUndefMacro(generatedFile, macroName);

	generatedFile.writeLines("#define " + macroName + "\t\\",
								"	inline rfk::NamespaceFragmentRegisterer " + getNamespaceFragmentRegistererName(generatedFile, namespaceInfo) +
								" = rfk::NamespaceFragmentRegisterer(\"" +
								namespaceInfo.name + "\", " +
								entityId + ", " +
								"&" + getGetNamespaceFragmentFunctionName(generatedFile, namespaceInfo) + "(), " +
								((namespaceInfo.outerEntity == nullptr) ? "true" : "false") +
								");");

	generatedFile.writeLine("");

	return macroName;
}

std::string GeneratedNamespaceCodeTemplate::getGetNamespaceFragmentFunctionName(kodgen::GeneratedFile const& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	return "getNamespaceFragment" + getEntityId(namespaceInfo) + "_" + std::to_string(stringHasher(generatedFile.getSourceFilePath().string()));
}

std::string GeneratedNamespaceCodeTemplate::getNamespaceFragmentRegistererName(kodgen::GeneratedFile const& generatedFile, kodgen::NamespaceInfo const&	namespaceInfo) const noexcept
{
	return "namespaceFragmentRegisterer" + getEntityId(namespaceInfo) + "_" + std::to_string(stringHasher(generatedFile.getSourceFilePath().string()));
}