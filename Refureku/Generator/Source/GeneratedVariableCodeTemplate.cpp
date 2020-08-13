#include "RefurekuGenerator/GeneratedVariableCodeTemplate.h"

#include <cassert>

#include "RefurekuGenerator/FileParser.h"

using namespace rfk;

std::string GeneratedVariableCodeTemplate::generateGetVariableDefinition(kodgen::GeneratedFile& generatedFile, kodgen::VariableInfo const& varInfo) const noexcept
{
	std::string macroName	= internalPrefix + getCurrentEntityId() + "_GenerateGetVariableDefinition";
	std::string properties;

	generatedFile.writeLines("#define " + macroName + "\t\\",
							 "	rfk::Variable const& " + getGetVariableFunctionName(varInfo) + "() noexcept\t\\",
							 "	{\t\\",
							 "		static bool				initialized = false;\t\\",
							 "		static rfk::Variable	variable(\"" + varInfo.name + "\", " +
																	 getCurrentEntityId() + ", "
																	 "rfk::Type::getType<" + varInfo.type.getCanonicalName() + ">(), "
																	 "&" + varInfo.getFullName() + ", "
																	 "static_cast<rfk::EVarFlags>(" + std::to_string(computeVarFlags(varInfo)) + ")"
																	 ");\t\\");

	generatedFile.writeLines("		if (!initialized)\t\\",
							 "		{\t\\",
							 "			initialized = true;\t\\");

	//Fill enum properties
	properties = fillEntityProperties(varInfo, "variable.");
	if (!properties.empty())
	{
		generatedFile.writeLine("			" + properties + "\t\\");
	}

	generatedFile.writeLine("		}\t\\");

	generatedFile.writeLines("		return variable;\t\\",
							 "	}\n");

	return macroName;
}

std::string GeneratedVariableCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::VariableInfo const& varInfo) const noexcept
{
	//Don't register to database if the class is contained in another entity (namespace / class)
	if (varInfo.outerEntity != nullptr)
	{
		return std::string();
	}
	else
	{
		std::string macroName = internalPrefix + getCurrentEntityId() + "_RegisterVariable";

		//Wrap into a generated namespace to avoid pollution in rfk namespace
		generatedFile.writeMacro(std::string(macroName),
								 "inline rfk::VariableRegisterer registerer" + getCurrentEntityId() + " = &getVariable" + getCurrentEntityId() + "();");

		return macroName;
	}
}

void GeneratedVariableCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) noexcept
{
	GeneratedEntityCodeTemplate::generateCode(generatedFile, entityInfo);

	assert(entityInfo.entityType == kodgen::EEntityType::Variable);

	kodgen::VariableInfo const& varInfo = static_cast<kodgen::VariableInfo const&>(entityInfo);

	std::string	mainMacroName		= internalPrefix + getCurrentEntityId() + "_GENERATED";

	std::string variableDefinition	= generateGetVariableDefinition(generatedFile, varInfo);
	std::string variableRegisterer	= generateRegistrationMacro(generatedFile, varInfo);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParser::parsingMacro);

	generatedFile.writeMacro(std::string(mainMacroName));

	generatedFile.writeLine("#else");

	generatedFile.writeMacro(std::move(mainMacroName),
							 "namespace rfk::generated {",
							 std::move(variableDefinition),
							 std::move(variableRegisterer),
							 "}");

	generatedFile.writeLine("#endif\n");
}

kodgen::uint8 GeneratedVariableCodeTemplate::computeVarFlags(kodgen::VariableInfo const& varInfo) const noexcept
{
	kodgen::uint8 result = 0u;

	if (varInfo.isStatic)
	{
		result |= 1 << 0;
	}

	return result;
}

std::string GeneratedVariableCodeTemplate::getGetVariableFunctionName(kodgen::VariableInfo const& varInfo) noexcept
{
	return "getVariable" + std::to_string(stringHasher(varInfo.id)) + "u";
}