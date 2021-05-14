#include "RefurekuGenerator/CodeGen/GeneratedFunctionCodeTemplate.h"

#include <cassert>

#include <Kodgen/Parsing/FileParserFactoryBase.h>

using namespace rfk;

std::string GeneratedFunctionCodeTemplate::generateGetFunctionDefinition(kodgen::GeneratedFile& generatedFile, kodgen::FunctionInfo const& funcInfo) const noexcept
{
	std::string entityId	= getEntityId(funcInfo);
	std::string macroName	= internalPrefix + entityId + "_GenerateGetFunctionDefinition";
	std::string generatedCode;
	std::string nonMemberFuncType = "rfk::NonMemberFunction<" + funcInfo.getPrototype(true) + ">";

	generatedFile.writeLines("#define " + macroName + "\t\\",
							 "\tinline rfk::Function const& " + getGetFunctionFunctionName(funcInfo) + "() noexcept\t\\",
							 "\t{\t\\",
							 "\t\tstatic bool				initialized = false;\t\\",
							 "\t\tstatic rfk::Function	function(\"" + funcInfo.name + "\", " +
																	 entityId + ", "
																	 "rfk::Type::getType<" + funcInfo.returnType.getCanonicalName() + ">(), "
																	 "std::unique_ptr<" + nonMemberFuncType + ">(new " + nonMemberFuncType + "(&" + funcInfo.getFullName() + ")), "
																	 "static_cast<rfk::EFunctionFlags>(" + std::to_string(computeFunctionFlags(funcInfo)) + ")"
																	 ");\t\\");

	generatedFile.writeLines("\t\tif (!initialized)\t\\",
							 "\t\t{\t\\",
							 "\t\t\tinitialized = true;\t\\");

	//Fill enum properties
	generatedCode = fillEntityProperties(funcInfo, "function.");
	if (!generatedCode.empty())
	{
		generatedFile.writeLine("\t\t\t" + generatedCode + "\t\\");
	}

	//Setup parameters
	if (!funcInfo.parameters.empty())
	{
		generatedFile.writeLine("\t\t\tfunction.parameters.reserve(" + std::to_string(funcInfo.parameters.size()) + ");\t\\");

		generatedCode = "\t\t\trfk::Function* functionPtr = &function; functionPtr";

		for (kodgen::FunctionParamInfo const& param : funcInfo.parameters)
		{
			generatedCode += "->addParameter(\"" + param.name + "\", rfk::Type::getType<" + param.type.getName() + ">())";
		}

		generatedFile.writeLine(generatedCode + ";\t\\");
	}

	generatedFile.writeLine("\t\t}\t\\");

	generatedFile.writeLines("\t\treturn function;\t\\",
							 "\t}\n");

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
		std::string entityId	= getEntityId(funcInfo);
		std::string macroName	= internalPrefix + entityId + "_RegisterFunction";

		generatedFile.writeMacro(std::string(macroName),
								 "inline rfk::DefaultEntityRegisterer registerer" + entityId + " = &" + getGetFunctionFunctionName(funcInfo) + "();");

		return macroName;
	}
}

void GeneratedFunctionCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& entityInfo, kodgen::FileGenerationUnit& fgu, kodgen::FileParsingResult const& parsingResult, std::string& out_errorDescription) const noexcept
{
	GeneratedEntityCodeTemplate::generateCode(generatedFile, entityInfo, fgu, parsingResult, out_errorDescription);

	assert(entityInfo.entityType == kodgen::EEntityType::Function);

	kodgen::FunctionInfo const& funcInfo = static_cast<kodgen::FunctionInfo const&>(entityInfo);

	std::string	mainMacroName		= internalPrefix + getEntityId(entityInfo) + "_GENERATED";

	std::string functionDefinition	= generateGetFunctionDefinition(generatedFile, funcInfo);
	std::string functionRegisterer	= generateRegistrationMacro(generatedFile, funcInfo);

	//Use parsing macro to avoid parsing generated data
	generatedFile.writeLine("#ifdef " + kodgen::FileParserFactoryBase::parsingMacro);

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
	return "getFunction" + getEntityId(funcInfo);
}