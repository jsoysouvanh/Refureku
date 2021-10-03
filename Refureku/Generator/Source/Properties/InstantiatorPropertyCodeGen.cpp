#include "RefurekuGenerator/Properties/InstantiatorPropertyCodeGen.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

using namespace rfk;

InstantiatorPropertyCodeGen::InstantiatorPropertyCodeGen() noexcept:
	kodgen::MacroPropertyCodeGen("Instantiator", kodgen::EEntityType::Method)
{
}

bool InstantiatorPropertyCodeGen::generateClassFooterCodeForEntity(kodgen::EntityInfo const& entity, kodgen::Property const& /*property*/, kodgen::uint8 /*propertyIndex*/,
																kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	kodgen::MethodInfo const&	method		= static_cast<kodgen::MethodInfo const&>(entity);
	std::string					className	= method.outerEntity->getFullName();
	std::string					parameters	= method.getParameterTypes();
	std::string					methodPtr	= "&" + className + "::" + method.name;

	if (parameters.empty())
	{
		//CustomIntantiator with no parameters
		inout_result += "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + ")>, \"[Refureku] Instantiator requires " + methodPtr + " to be a static method returning " + className + "* .\");" + env.getSeparator();
	}
	else
	{
		inout_result += "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + "), " + std::move(parameters) + ">, \"[Refureku] Instantiator requires " + methodPtr + " to be a static method returning " + className + "*.\");" + env.getSeparator();
	}

	return true;
}

void InstantiatorPropertyCodeGen::addCustomInstantiatorToClass(kodgen::MethodInfo const& method, std::string const& generatedClassVariableName,
																	 std::string const& generatedMethodVarName, std::string& inout_result) const noexcept
{
	inout_result += generatedClassVariableName + "addCustomInstantiator<" + method.returnType.getCanonicalName() + ">(" + generatedMethodVarName + "); ";	//TODO: addInstantiator
}