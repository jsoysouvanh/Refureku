#include "GeneratedNamespaceCodeTemplate.h"

#include <cassert>

using namespace rfk;

void GeneratedNamespaceCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) noexcept
{
	GeneratedEntityCodeTemplate::generateCode(generatedFile, entityInfo);

	assert(entityInfo.entityType == kodgen::EntityInfo::EType::Namespace);

	kodgen::NamespaceInfo const& namespaceInfo = static_cast<kodgen::NamespaceInfo const&>(entityInfo);

	std::string	mainMacroName						= internalPrefix + getCurrentEntityId() + "_GENERATED";
	std::string fillNamespaceDeclarationMacroName	= generateFillNamespaceDeclarationMacro(generatedFile, namespaceInfo);
	std::string fillNamespaceDefinitionMacroName	= generateFillNamespaceDefinitionMacro(generatedFile, namespaceInfo);
	std::string registerMacroName					= generateRegistrationMacro(generatedFile, namespaceInfo);

	generatedFile.writeMacro(std::move(mainMacroName),
							 "namespace rfk::generated {",
							 std::move(fillNamespaceDeclarationMacroName),
							 std::move(registerMacroName),
							 std::move(fillNamespaceDefinitionMacroName),
							 "}");
}

std::string GeneratedNamespaceCodeTemplate::generateFillNamespaceDeclarationMacro(kodgen::GeneratedFile& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	std::string macroName = internalPrefix + getCurrentEntityId() + "_DeclareFillNamespace";

	generatedFile.writeLines("#define " + macroName + " inline void " + getFillNamespaceFunctionName(generatedFile) + "([[maybe_unused]] rfk::Namespace* n) noexcept;",
							 "");

	return macroName;
}

std::string GeneratedNamespaceCodeTemplate::generateFillNamespaceDefinitionMacro(kodgen::GeneratedFile& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	std::string macroName = internalPrefix + getCurrentEntityId() + "_DefineFillNamespace";

	generatedFile.writeLines("#define " + macroName + "\t\\",
							 "	inline void " + getFillNamespaceFunctionName(generatedFile) + "([[maybe_unused]] rfk::Namespace* n) noexcept {\t\\");

	//Fill namespace properties
	std::string properties = fillEntityProperties(namespaceInfo, "n->");
	if (!properties.empty())
	{
		generatedFile.writeLine("		" + properties + "\t\\");
	}

	//Fill nested namespaces
	if (!namespaceInfo.namespaces.empty())
	{
		//Reserve space first
		generatedFile.writeLines("		std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName>::iterator	valueIt;\t\\",
								 "		n->nestedNamespaces.reserve(" + std::to_string(namespaceInfo.namespaces.size()) + "u);\t\\");

		for (kodgen::NamespaceInfo const& nestedNamespaceInfo : namespaceInfo.namespaces)
		{
			generatedFile.writeLine("		n->nestedNamespaces.emplace(" + getNamespaceRegistererName(generatedFile, nestedNamespaceInfo) + ".getNamespaceInstance());\t\\");
		}
	}

	//Fill nested archetypes
	//TODO

	generatedFile.writeLines("	}",
							 "");

	return macroName;
}

std::string GeneratedNamespaceCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::NamespaceInfo const& namespaceInfo) const noexcept
{
	////Don't register to database if the namespace is contained in another namespace
	//if (namespaceInfo.outerEntity != nullptr)
	//{
	//	return std::string();
	//}
	//else
	//{
		std::string macroName = internalPrefix + getCurrentEntityId() + "_RegisterNamespace";

		generatedFile.writeLines("#define " + macroName + "\t\\",
								 "	inline rfk::NamespaceRegisterer " + getNamespaceRegistererName(generatedFile, namespaceInfo) +
								 " = rfk::NamespaceRegisterer(\"" + namespaceInfo.name + "\", " + getCurrentEntityId() + "u, &" + getFillNamespaceFunctionName(generatedFile) + ");");

		generatedFile.writeLine("");

		return macroName;
//	}
}

std::string GeneratedNamespaceCodeTemplate::getFillNamespaceFunctionName(kodgen::GeneratedFile const& generatedFile) const noexcept
{
	return "fillNamespace_" + getCurrentEntityId() + "_" + std::to_string(stringHasher(generatedFile.getSourceFilePath().string()));
}

std::string GeneratedNamespaceCodeTemplate::getNamespaceRegistererName(kodgen::GeneratedFile const& generatedFile, kodgen::NamespaceInfo const&	namespaceInfo) const noexcept
{
	return "namespaceRegisterer" + std::to_string(stringHasher(namespaceInfo.id)) + "_" + std::to_string(stringHasher(generatedFile.getSourceFilePath().string()));
}