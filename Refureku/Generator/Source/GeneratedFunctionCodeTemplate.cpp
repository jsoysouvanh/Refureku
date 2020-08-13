#include "RefurekuGenerator/GeneratedFunctionCodeTemplate.h"

#include <cassert>

#include "RefurekuGenerator/FileParser.h"

using namespace rfk;

std::string GeneratedFunctionCodeTemplate::generateGetFunctionDefinition(kodgen::GeneratedFile& generatedFile, kodgen::FunctionInfo const& funcInfo) const noexcept
{
	std::string macroName	= internalPrefix + getCurrentEntityId() + "_GenerateGetFunctionDefinition";
	std::string properties;
	std::string nonMemberFuncType = "rfk::NonMemberFunction<" + funcInfo.getPrototype(true, true) + ">";

	generatedFile.writeLines("#define " + macroName + "\t\\",
							 "	rfk::Function const& " + getGetFunctionFunctionName(funcInfo) + "() noexcept\t\\",
							 "	{\t\\",
							 "		static bool				initialized = false;\t\\",
							 "		static rfk::Function	function(\"" + funcInfo.name + "\", " +
																	 getCurrentEntityId() + ", "
																	 "rfk::Type::getType<" + funcInfo.returnType.getCanonicalName() + ">(), "
																	 "std::unique_ptr<" + nonMemberFuncType + ">(new " + nonMemberFuncType + "(&" + funcInfo.getFullName() + ")), "
																	 "static_cast<rfk::EFunctionFlags>(" + std::to_string(computeFunctionFlags(funcInfo)) + ")"
																	 ");\t\\");

	generatedFile.writeLines("		if (!initialized)\t\\",
							 "		{\t\\",
							 "			initialized = true;\t\\");

	//Fill enum properties
	properties = fillEntityProperties(funcInfo, "function.");
	if (!properties.empty())
	{
		generatedFile.writeLine("			" + properties + "\t\\");
	}

	//Setup parameters
	if (!funcInfo.parameters.empty())
	{
		generatedFile.writeLine("	function.parameters.reserve(" + std::to_string(funcInfo.parameters.size()) + ");\t\\");

		for (kodgen::FunctionParamInfo const& param : funcInfo.parameters)
		{
			generatedFile.writeLine("	function.parameters.emplace_back(\"" + param.name + "\", rfk::Type::getType<" + param.type.getName() + ">());\t\\");
		}
	}

	generatedFile.writeLine("		}\t\\");

	generatedFile.writeLines("		return function;\t\\",
							 "	}\n");

	return macroName;
}

std::string GeneratedFunctionCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::FunctionInfo const& funcInfo) const noexcept
{
	//Don't register to database if the class is contained in another entity (namespace / class)
	if (funcInfo.outerEntity != nullptr)
	{
		return std::string();
	}
	else
	{
		std::string macroName = internalPrefix + getCurrentEntityId() + "_RegisterFunction";

		generatedFile.writeMacro(std::string(macroName),
								 "inline rfk::DefaultEntityRegisterer registerer" + getCurrentEntityId() + " = &" + getGetFunctionFunctionName(funcInfo) + "();");

		return macroName;
	}
}

void GeneratedFunctionCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) noexcept
{
	GeneratedEntityCodeTemplate::generateCode(generatedFile, entityInfo);

	assert(entityInfo.entityType == kodgen::EEntityType::Function);

	kodgen::FunctionInfo const& funcInfo = static_cast<kodgen::FunctionInfo const&>(entityInfo);

	std::string	mainMacroName		= internalPrefix + getCurrentEntityId() + "_GENERATED";

	std::string functionDefinition	= generateGetFunctionDefinition(generatedFile, funcInfo);
	std::string functionRegisterer	= generateRegistrationMacro(generatedFile, funcInfo);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParser::parsingMacro);

	generatedFile.writeMacro(std::string(mainMacroName));

	generatedFile.writeLine("#else");

	generatedFile.writeMacro(std::move(mainMacroName),
							 "namespace rfk::generated {",
							 std::move(functionDefinition),
							 std::move(functionRegisterer),
							 "}");

	generatedFile.writeLine("#endif\n");
}

kodgen::uint8 GeneratedFunctionCodeTemplate::computeFunctionFlags(kodgen::FunctionInfo const& funcInfo) const noexcept
{
	kodgen::uint8 result = 0u;

	if (funcInfo.isStatic)
	{
		result |= 1 << 0;
	}

	if (funcInfo.isInline)
	{
		result |= 1 << 1;
	}

	return result;
}

std::string GeneratedFunctionCodeTemplate::getGetFunctionFunctionName(kodgen::FunctionInfo const& funcInfo) noexcept
{
	return "getFunction" + std::to_string(stringHasher(funcInfo.id)) + "u";
}