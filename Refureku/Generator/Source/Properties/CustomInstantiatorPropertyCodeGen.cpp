#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyCodeGen.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

#include "RefurekuGenerator/Properties/NativeProperties.h"

using namespace rfk;

CustomInstantiatorPropertyCodeGen::CustomInstantiatorPropertyCodeGen() noexcept:
	kodgen::MacroPropertyCodeGen("CustomInstantiator", kodgen::EEntityType::Method)
{
}

bool CustomInstantiatorPropertyCodeGen::generateClassFooterCode(kodgen::EntityInfo const* entity, kodgen::Property const* property,
																kodgen::uint8 /*propertyIndex*/, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	assert(entity != nullptr);

	kodgen::MethodInfo const*	method		= reinterpret_cast<kodgen::MethodInfo const*>(entity);
	std::string					className	= entity->outerEntity->getFullName();
	std::string					parameters	= method->getParameterTypes();
	std::string					methodPtr	= "&" + className + "::" + method->name;

	if (parameters.empty())
	{
		//CustomIntantiator with no parameters
		inout_result += "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + ")>, \"[Refureku] CustomInstantiator requires " + methodPtr + " to be a static method returning " + className + "* .\");" + env.getSeparator();
	}
	else
	{
		inout_result += "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + "), " + std::move(parameters) + ">, \"[Refureku] CustomInstantiator requires " + methodPtr + " to be a static method returning " + className + "*.\");" + env.getSeparator();
	}

	return true;
}

void CustomInstantiatorPropertyCodeGen::addCustomInstantiatorToClass(kodgen::MethodInfo const& method, std::string const& generatedClassVariableName,
																	 std::string const& generatedMethodVarName, std::string& inout_result) const noexcept
{
	inout_result += generatedClassVariableName + "addCustomInstantiator<" + method.returnType.getCanonicalName() + ">(" + generatedMethodVarName + "); ";
}